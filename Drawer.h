//
// Created by Jan Skála on 25.04.2017.
//

#ifndef UDPTASK_DRAWER_H
#define UDPTASK_DRAWER_H

#define WIDTH 480
#define HEIGHT 320

#define _POSIX_C_SOURCE 200112L
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <byteswap.h>
#include <getopt.h>
#include <inttypes.h>
#include <time.h>
char *memdev = (char *) "/dev/mem";
#define SPILED_REG_BASE_PHYS 0x43c40000
#define SPILED_REG_SIZE      0x00004000
#define SPILED_REG_LED_LINE_o           0x004
#define SPILED_REG_LED_RGB1_o           0x010
#define SPILED_REG_LED_RGB2_o           0x014
#define SPILED_REG_LED_KBDWR_DIRECT_o   0x018
#define SPILED_REG_KBDRD_KNOBS_DIRECT_o 0x020
#define SPILED_REG_KNOBS_8BIT_o         0x024
#define PARLCD_REG_BASE_PHYS 0x43c00000
#define PARLCD_REG_SIZE      0x00004000
#define PARLCD_REG_CMD_o                0x0008
#define PARLCD_REG_DATA_o               0x000C

class Drawer {
public:
    Drawer();
    void DrawPixels();
    void AddRectangle(int x, int y, int width, int height, uint16_t color);
    ~Drawer();

private:
    uint16_t pixels[320][480];
    unsigned char *parlcd_mem_base;

    void *map_phys_address(off_t region_base, size_t region_size, int opt_cached);
    void parlcd_write_cmd(unsigned char *parlcd_mem_base, uint16_t cmd);
    void parlcd_write_data(unsigned char *parlcd_mem_base, uint16_t data);
    void parlcd_write_data2x(unsigned char *parlcd_mem_base, uint32_t data);
    void parlcd_delay(int msec);
    void parlcd_hx8357_init(unsigned char *parlcd_mem_base);
};


#endif //UDPTASK_DRAWER_H
