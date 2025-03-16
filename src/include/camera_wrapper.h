#ifndef CAMERA_WRAPPER_H
#define CAMERA_WRAPPER_H

// High-Level Explanation:
// This module provides a wrapper around OpenCV's video capture and writing functionalities to manage camera input and video saving.
// It encapsulates a camera capture object, a frame buffer, and a video writer, enabling real-time frame capture and optional saving to a file.
// The code is designed to mimic the behavior of a QNX-based version, supporting toggle saving with 's' and exit with 'q' in a broader application context.
// Important functions handle initialization, frame capture, saving control, and resource cleanup.
// Key variables include the camera capture object, frame data, video writer, resolution settings, saving state, and output file path.

// Important Functions:
// - camera_init: Initializes the camera with specified width, height, and output filename.
// - camera_capture_frame: Captures a frame from the camera and provides raw pixel data.
// - camera_start_saving: Starts video recording to the specified file.
// - camera_stop_saving: Stops video recording and releases the writer.
// - camera_is_saving: Checks the current saving state.
// - camera_release: Cleans up all resources, including camera and writer.

// Important Variables:
// - cap: OpenCV VideoCapture object for camera input.
// - frame: OpenCV Mat object storing the current frame.
// - writer: OpenCV VideoWriter object for saving frames.
// - width/height: Resolution settings for the camera.
// - is_saving: Flag to indicate if video saving is active.
// - output_filename: Path for the output video file.

// Inputs and Outputs:
// - Inputs: width (int), height (int), output_filename (const char*).
// - Outputs: data (unsigned char**), width (int*), height (int*), return codes (int).

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