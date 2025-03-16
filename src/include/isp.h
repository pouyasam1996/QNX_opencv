#ifndef ISP_H
#define ISP_H

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