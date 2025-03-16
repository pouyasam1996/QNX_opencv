#ifndef CAMERA_WRAPPER_H
#define CAMERA_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct CameraWrapper CameraWrapper;

    // Initialize the camera
    CameraWrapper* camera_init(int width, int height, const char* output_filename);

    // Capture a frame (returns pointer to raw pixel data and dimensions)
    int camera_capture_frame(CameraWrapper* wrapper, unsigned char** data, int* width, int* height);

    // Start saving video
    int camera_start_saving(CameraWrapper* wrapper);

    // Stop saving video
    int camera_stop_saving(CameraWrapper* wrapper);

    // Check if currently saving
    int camera_is_saving(CameraWrapper* wrapper);

    // Release resources
    void camera_release(CameraWrapper* wrapper);

#ifdef __cplusplus
}
#endif

#endif // CAMERA_WRAPPER_H