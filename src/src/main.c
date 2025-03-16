#include "isp.h"
#include "display.h"
#include "encoder.h"
#include "camera_wrapper.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

display *global_display;
encoder *global_encoder;
CameraWrapper *camera;
int is_encoding = 0;
pthread_t encoder_thread_id;
pthread_mutex_t camera_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t encode_mutex = PTHREAD_MUTEX_INITIALIZER;

void isp_callback(isp *isp_camera) {
    int width, height;
    unsigned char *data = isp_get_current_buffer(isp_camera, &width, &height);
    display_display_data(global_display, data, width, height, camera_is_saving(camera)); // Pass saving status
}

void display_callback(void) {
}

void *encoder_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&camera_mutex);
        pthread_mutex_lock(&encode_mutex);
        if (!is_encoding) {
            pthread_mutex_unlock(&encode_mutex);
            pthread_mutex_unlock(&camera_mutex);
            printf("Encoder thread exiting...\n");
            break;
        }
        pthread_mutex_unlock(&encode_mutex);

        int width, height;
        unsigned char *data;
        if (camera_capture_frame(camera, &data, &width, &height) != 0) {
            printf("Failed to capture frame for encoding!\n");
            pthread_mutex_unlock(&camera_mutex);
            break;
        }
        pthread_mutex_unlock(&camera_mutex);

        encoder_encode_frame(global_encoder, (int *)data);
        usleep(10000);
    }
    return NULL;
}

int main() {
    isp *isp_camera;
    display *screen;
    encoder *recorder;

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Failed to get current working directory!\n");
        return 1;
    }

    char output_path[PATH_MAX];
    snprintf(output_path, sizeof(output_path), "%s/../output/output_video.mp4", cwd);

    camera = camera_init(1280, 720, output_path);
    if (!camera) {
        printf("Failed to initialize camera!\n");
        return 1;
    }
    printf("Camera, ISP, Display, and Encoder initialized.\n");

    if (isp_init(&isp_camera, isp_callback) != 0) {
        printf("ISP init failed!\n");
        camera_release(camera);
        return 1;
    }

    if (display_init(&screen, display_callback) != 0) {
        printf("Display init failed!\n");
        isp_uninit(isp_camera);
        camera_release(camera);
        return 1;
    }

    if (encoder_init(&recorder, output_path) != 0) {
        printf("Encoder init failed!\n");
        display_uninit(screen);
        isp_uninit(isp_camera);
        camera_release(camera);
        return 1;
    }
    global_display = screen;
    global_encoder = recorder;

    pthread_mutex_lock(&encode_mutex);
    is_encoding = 1;
    if (pthread_create(&encoder_thread_id, NULL, encoder_thread, NULL) != 0) {
        printf("Encoder thread creation failed!\n");
        pthread_mutex_unlock(&encode_mutex);
        encoder_uninit(recorder);
        display_uninit(screen);
        isp_uninit(isp_camera);
        camera_release(camera);
        return 1;
    }
    pthread_mutex_unlock(&encode_mutex);
    printf("Press 's' to toggle saving, 'q' to quit.\n");

    while (1) {
        int width, height;
        unsigned char *data;
        pthread_mutex_lock(&camera_mutex);
        if (camera_capture_frame(camera, &data, &width, &height) != 0) {
            printf("Failed to capture frame!\n");
            pthread_mutex_unlock(&camera_mutex);
            break;
        }
        pthread_mutex_unlock(&camera_mutex);

        isp_program_R0(isp_camera, data, width, height);
        isp_program_R1(isp_camera, data, width, height);
        isp_start(isp_camera);

        display_display_data(global_display, data, width, height, camera_is_saving(camera));

        int key = display_get_keypress();
        if (key == 's') {
            if (!camera_is_saving(camera)) {
                if (camera_start_saving(camera) == 0) {
                    printf("Started saving video to %s\n", output_path);
                } else {
                    printf("Failed to start saving video!\n");
                }
            } else {
                camera_stop_saving(camera);
                printf("Stopped saving video.\n");
            }
        } else if (key == 'q') {
            if (camera_is_saving(camera)) {
                camera_stop_saving(camera);
                printf("Stopped saving video.\n");
            }
            pthread_mutex_lock(&encode_mutex);
            is_encoding = 0;
            pthread_mutex_unlock(&encode_mutex);
            break;
        }
    }

    pthread_join(encoder_thread_id, NULL);
    encoder_finalize_recording(recorder);
    printf("Saving stopped and file finalized.\n");

    printf("Cleanup completed.\n");
    encoder_uninit(recorder);
    display_uninit(screen);
    isp_uninit(isp_camera);
    camera_release(camera);
    return 0;
}