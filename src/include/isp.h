#ifndef ISP_H
#define ISP_H

// High-Level Explanation:
// This module implements an Image Signal Processor (ISP) for double-buffering video frames in an OpenCV-based video pipeline.
// It manages two buffers (R0 and R1) to alternate between frame capture and display, ensuring smooth processing in a multi-threaded environment.
// The code integrates with the camera wrapper and display modules, supporting toggle saving with 's' and exit with 'q' in the broader application.
// Important functions initialize the ISP, program buffers, start processing, and retrieve the current buffer for display.
// Key variables include buffer data, dimensions, and the current buffer state.

// Important Functions:
// - isp_init: Initializes the ISP with a callback for frame processing.
// - isp_uninit: Releases ISP resources.
// - isp_program_R0/R1: Programs the R0 or R1 buffer with frame data.
// - isp_start: Triggers the callback to process the current frame.
// - isp_get_current_buffer: Retrieves the current buffer for display.

// Important Variables:
// - callback: Function pointer to process frames after buffering.
// - r0_data/r1_data: Frame data for R0 and R1 buffers.
// - r0_width/r0_height, r1_width/r1_height: Dimensions of each buffer.
// - current_buffer: Indicates the active buffer (0 for R0, 1 for R1).

// Inputs and Outputs:
// - Inputs: callback (void (*)), data (unsigned char*), width (int), height (int).
// - Outputs: data (unsigned char*), width (int*), height (int*), return codes (int).
// Forward declaration of struct isp
struct isp;

// Define the isp type as a pointer to struct isp
typedef struct isp isp;

// Function declarations using the struct isp type
int isp_init(isp **isp, void (*callback)(struct isp *));
int isp_uninit(isp *isp);
int isp_program_R0(isp *isp, unsigned char *data, int width, int height);
int isp_program_R1(isp *isp, unsigned char *data, int width, int height);
int isp_start(isp *isp);
unsigned char* isp_get_current_buffer(isp *isp, int *width, int *height);

// Now define the struct isp
struct isp {
    void (*callback)(struct isp *); // Callback function pointer
    unsigned char *r0_data;
    unsigned char *r1_data;
    int r0_width, r0_height;
    int r1_width, r1_height;
    int current_buffer; // 0 for R0, 1 for R1
};

#endif