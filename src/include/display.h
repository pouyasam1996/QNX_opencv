#ifndef DISPLAY_H
#define DISPLAY_H
// High-Level Explanation:
// This module manages the display of video frames using OpenCV's high-level GUI functions (cv::imshow, cv::namedWindow).
// It creates a window, renders frames with a "Saving Video" or "Not Saving" status overlay, and captures keypresses to support user interaction ('s' to toggle saving, 'q' to quit).
// The code is part of an OpenCV-based video pipeline, designed to work with a camera wrapper, encoder, and ISP for real-time video processing.
// Important functions initialize the display, render frames, detect keypresses, and clean up resources.
// Key variables include the display structure, initialization state, and callback for frame processing.

// Important Functions:
// - display_init: Initializes the display with a callback for frame processing.
// - display_uninit: Frees display resources.
// - display_display_data: Renders a frame with a saving status overlay using OpenCV.
// - display_get_keypress: Captures user keypresses ('s' or 'q') using OpenCV's waitKey.

// Important Variables:
// - callback: Function pointer for post-display processing.
// - is_initialized: Flag indicating if the display is initialized.

// Inputs and Outputs:
// - Inputs: display_callback (void (*)), data (unsigned char*), width (int), height (int), is_saving (int).
// - Outputs: Return codes (int), keypress (int).

#ifdef __cplusplus
extern "C" {
#endif

    typedef void* display;

    int display_init(display **disp, void (*display_callback)(void));
    int display_uninit(display *disp);
    int display_display_data(display *disp, unsigned char *data, int width, int height, int is_saving); // Matches updated signature
    int display_get_keypress(void);

#ifdef __cplusplus
}
#endif

#endif