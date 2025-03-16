#include "camera_wrapper.h"
#include <opencv2/opencv.hpp>

struct CameraWrapper {
    cv::VideoCapture cap;
    cv::Mat frame;
    cv::VideoWriter writer;
    int width;
    int height;
    int is_saving;
    std::string output_filename;
};

CameraWrapper* camera_init(int width, int height, const char* output_filename) {
    CameraWrapper* wrapper = new CameraWrapper();
    wrapper->cap = cv::VideoCapture(0); // Default camera
    if (!wrapper->cap.isOpened()) {
        delete wrapper;
        return nullptr;
    }

    // Set camera resolution
    wrapper->cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    wrapper->cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    wrapper->width = width;
    wrapper->height = height;
    wrapper->is_saving = 0;
    wrapper->output_filename = output_filename;

    return wrapper;
}

int camera_capture_frame(CameraWrapper* wrapper, unsigned char** data, int* width, int* height) {
    if (!wrapper || !wrapper->cap.isOpened()) {
        return -1;
    }

    wrapper->cap >> wrapper->frame;
    if (wrapper->frame.empty()) {
        return -1;
    }

    *data = wrapper->frame.data; // Raw pixel data (BGR format)
    *width = wrapper->frame.cols;
    *height = wrapper->frame.rows;

    // Save the frame if recording is active
    if (wrapper->is_saving && wrapper->writer.isOpened()) {
        wrapper->writer.write(wrapper->frame);
    }

    return 0;
}

int camera_start_saving(CameraWrapper* wrapper) {
    if (!wrapper || wrapper->is_saving) return -1;

    wrapper->writer = cv::VideoWriter(
        wrapper->output_filename,
        cv::VideoWriter::fourcc('H', '2', '6', '4'),
        30,
        cv::Size(wrapper->width, wrapper->height)
    );
    if (!wrapper->writer.isOpened()) {
        return -1;
    }
    wrapper->is_saving = 1;
    return 0;
}

int camera_stop_saving(CameraWrapper* wrapper) {
    if (!wrapper || !wrapper->is_saving) return -1;
    wrapper->is_saving = 0;
    wrapper->writer.release();
    return 0;
}

int camera_is_saving(CameraWrapper* wrapper) {
    if (!wrapper) return 0;
    return wrapper->is_saving;
}

void camera_release(CameraWrapper* wrapper) {
    if (wrapper) {
        if (wrapper->is_saving) {
            wrapper->is_saving = 0;
            wrapper->writer.release();
        }
        wrapper->cap.release();
        delete wrapper;
    }
    cv::destroyAllWindows();
}