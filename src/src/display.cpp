#include "display.h"
#include <stdlib.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>

typedef struct {
    void (*callback)(void);
    int is_initialized;
} display_t;

extern "C" {
    int display_init(display **disp, void (*display_callback)(void)) {
        display_t *new_display = (display_t *)malloc(sizeof(display_t));
        if (!new_display) return -1;
        new_display->callback = display_callback;
        new_display->is_initialized = 1;
        *disp = (display *)new_display;
        return 0;
    }

    int display_uninit(display *disp) {
        if (!disp) return -1;
        ((display_t *)disp)->is_initialized = 0;
        free(disp);
        return 0;
    }

    int display_display_data(display *disp, unsigned char *data, int width, int height, int is_saving) {
        if (!disp || !data) return -1;
        if (((display_t *)disp)->is_initialized == 0) return -1;

        cv::Mat frame(height, width, CV_8UC3, data);

        static int window_created = 0;
        if (!window_created) {
            cv::namedWindow("Live Camera", cv::WINDOW_NORMAL);
            window_created = 1;
        }

        std::string status_text = is_saving ? "Saving Video" : "Not Saving";
        int font_face = cv::FONT_HERSHEY_SIMPLEX;
        double font_scale = 1.0;
        int thickness = 2;
        cv::Scalar text_color = is_saving ? cv::Scalar(0, 255, 0) : cv::Scalar(0, 0, 255);
        int baseline = 0;
        cv::Size text_size = cv::getTextSize(status_text, font_face, font_scale, thickness, &baseline);
        int text_x = 10;
        int text_y = text_size.height + 10;
        cv::putText(frame, status_text, cv::Point(text_x, text_y), font_face, font_scale, text_color, thickness);

        cv::imshow("Live Camera", frame);

        if (((display_t *)disp)->callback) {
            ((display_t *)disp)->callback();
        }

        return 0;
    }

    int display_get_keypress(void) {
        return cv::waitKey(1);
    }
}