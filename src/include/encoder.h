#ifndef ENCODER_H
#define ENCODER_H

// High-Level Explanation:
// This module manages video frame encoding within an OpenCV-based video pipeline, currently serving as a placeholder for logging frame counts.
// It is designed to integrate with a camera wrapper and display module, supporting future enhancements like saving frames to a file (e.g., toggling with 's' and exiting with 'q').
// The code tracks frame counts and provides initialization, encoding, and finalization functions, with potential for expansion to handle video writing.
// Important functions handle encoder setup, frame encoding, and cleanup.
// Key variables include the output filename, initialization state, and frame counter.

// Important Functions:
// - encoder_init: Initializes the encoder with an output filename.
// - encoder_uninit: Releases encoder resources.
// - encoder_encode_frame: Logs a frame (placeholder for future encoding logic).
// - encoder_finalize_recording: Finalizes the encoding process and logs completion.

// Important Variables:
// - filename: Output filename (currently unused for saving, used for logging).
// - is_initialized: Flag indicating if the encoder is active.
// - frame_count: Tracks the number of encoded frames.

// Inputs and Outputs:
// - Inputs: out_filename (char*), address (int*).
// - Outputs: Return codes (int).

typedef struct encoder encoder;
int encoder_init(encoder **enc, char *out_filename);
int encoder_uninit(encoder *enc);
int encoder_encode_frame(encoder *enc, int *address);
int encoder_finalize_recording(encoder *enc);

#endif