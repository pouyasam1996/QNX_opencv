#ifndef DISPLAY_H
#define DISPLAY_H

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