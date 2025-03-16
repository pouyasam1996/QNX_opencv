#include "isp.h"
#include <stdlib.h>
#include <stdio.h>

int isp_init(isp **isp, void (*callback)(struct isp *)) {
    struct isp *new_isp = (struct isp *)malloc(sizeof(struct isp));
    if (!new_isp) return -1;
    new_isp->callback = callback;
    new_isp->r0_data = NULL;
    new_isp->r1_data = NULL;
    new_isp->current_buffer = 0;
    *isp = new_isp;
    return 0;
}

int isp_uninit(isp *isp) {
    if (!isp) return -1;
    free(isp);
    return 0;
}

int isp_program_R0(isp *isp, unsigned char *data, int width, int height) {
    if (!isp) return -1;
    isp->r0_data = data;
    isp->r0_width = width;
    isp->r0_height = height;
    return 0;
}

int isp_program_R1(isp *isp, unsigned char *data, int width, int height) {
    if (!isp) return -1;
    isp->r1_data = data;
    isp->r1_width = width;
    isp->r1_height = height;
    return 0;
}

int isp_start(isp *isp) {
    if (!isp || !isp->callback) return -1;
    isp->callback(isp);
    return 0;
}

unsigned char* isp_get_current_buffer(isp *isp, int *width, int *height) {
    if (!isp) return NULL;
    if (isp->current_buffer == 0) {
        *width = isp->r0_width;
        *height = isp->r0_height;
        isp->current_buffer = 1;
        return isp->r0_data;
    } else {
        *width = isp->r1_width;
        *height = isp->r1_height;
        isp->current_buffer = 0;
        return isp->r1_data;
    }
}