#include "encoder.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *filename;
    int is_initialized;
    int frame_count;
} encoder_t;

int encoder_init(encoder **enc, char *out_filename) {
    if (enc == NULL || out_filename == NULL) return -1;
    encoder_t *new_encoder = (encoder_t *)malloc(sizeof(encoder_t));
    if (new_encoder == NULL) return -1;
    new_encoder->filename = out_filename;
    new_encoder->is_initialized = 1;
    new_encoder->frame_count = 0;
    *enc = (encoder *)new_encoder;
    return 0;
}

int encoder_uninit(encoder *enc) {
    if (enc == NULL) return -1;
    ((encoder_t *)enc)->is_initialized = 0;
    free(enc);
    return 0;
}

int encoder_encode_frame(encoder *enc, int *address) {
    if (enc == NULL || address == NULL) return -1;
    if (((encoder_t *)enc)->is_initialized == 0) return -1;

    ((encoder_t *)enc)->frame_count++;
    //printf("Encoding frame %d...\n", ((encoder_t *)enc)->frame_count);

    return 0;
}

int encoder_finalize_recording(encoder *enc) {
    if (enc == NULL) return -1;
    if (((encoder_t *)enc)->is_initialized == 0) return -1;
    printf("Encoding finalized for file: %s\n", ((encoder_t *)enc)->filename);
    ((encoder_t *)enc)->is_initialized = 0;
    return 0;
}