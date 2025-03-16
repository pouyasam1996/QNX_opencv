#ifndef ENCODER_H
#define ENCODER_H

typedef struct encoder encoder;
int encoder_init(encoder **enc, char *out_filename);
int encoder_uninit(encoder *enc);
int encoder_encode_frame(encoder *enc, int *address);
int encoder_finalize_recording(encoder *enc);

#endif