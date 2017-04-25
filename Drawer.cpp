//
// Created by Jan Skála on 25.04.2017.
//

#include "Drawer.h"

Drawer::Drawer() {
    parlcd_mem_base = (unsigned char *) map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcd_mem_base == NULL)
        exit(1);
    //init display
    parlcd_hx8357_init(parlcd_mem_base);
}

void Drawer::DrawPixels() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            parlcd_write_data(parlcd_mem_base, 0xFFFF);
        }
    }
}

void *Drawer::map_phys_address(off_t region_base, size_t region_size, int opt_cached) {
    unsigned long mem_window_size;
    unsigned long pagesize;
    unsigned char *mm;
    unsigned char *mem;
    int fd;
    fd = open(memdev, O_RDWR | (!opt_cached ? O_SYNC : 0));
    if (fd < 0) {
        fprintf(stderr, "cannot open %s\n", memdev);
        return NULL;
    }
    pagesize = sysconf(_SC_PAGESIZE);
    mem_window_size = ((region_base & (pagesize - 1)) + region_size + pagesize - 1) & ~(pagesize - 1);
    mm = (unsigned char*) mmap(NULL, mem_window_size, PROT_WRITE | PROT_READ,
              MAP_SHARED, fd, region_base & ~(pagesize - 1));
    mem = mm + (region_base & (pagesize - 1));
    if (mm == MAP_FAILED) {
        fprintf(stderr, "mmap error\n");
        return NULL;
    }
    return mem;
}

void Drawer::parlcd_write_cmd(unsigned char *parlcd_mem_base, uint16_t cmd) {
    *(volatile uint16_t *) (parlcd_mem_base + PARLCD_REG_CMD_o) = cmd;
}

void Drawer::parlcd_write_data(unsigned char *parlcd_mem_base, uint16_t data) {
    *(volatile uint16_t *) (parlcd_mem_base + PARLCD_REG_DATA_o) = data;
}

void Drawer::parlcd_write_data2x(unsigned char *parlcd_mem_base, uint32_t data) {
    *(volatile uint32_t *) (parlcd_mem_base + PARLCD_REG_DATA_o) = data;
}

void Drawer::parlcd_delay(int msec) {
    struct timespec wait_delay = {.tv_sec = msec / 1000,
            .tv_nsec = (msec % 1000) * 1000 * 1000};
    clock_nanosleep(CLOCK_MONOTONIC, 0, &wait_delay, NULL);
}

void Drawer::parlcd_hx8357_init(unsigned char *parlcd_mem_base) {
    // toggle RST low to reset
/*
    digitalWrite(_rst, HIGH);
    parlcd_delay(50);
    digitalWrite(_rst, LOW);
    parlcd_delay(10);
    digitalWrite(_rst, HIGH);
    parlcd_delay(10);
*/
    parlcd_write_cmd(parlcd_mem_base, 0x1);
    parlcd_delay(30);
#ifdef HX8357_B
    // Configure HX8357-B display
        parlcd_write_cmd(parlcd_mem_base, 0x11);
        parlcd_delay(20);
        parlcd_write_cmd(parlcd_mem_base, 0xD0);
        parlcd_write_data(parlcd_mem_base, 0x07);
        parlcd_write_data(parlcd_mem_base, 0x42);
        parlcd_write_data(parlcd_mem_base, 0x18);
        parlcd_write_cmd(parlcd_mem_base, 0xD1);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_data(parlcd_mem_base, 0x07);
        parlcd_write_data(parlcd_mem_base, 0x10);
        parlcd_write_cmd(parlcd_mem_base, 0xD2);
        parlcd_write_data(parlcd_mem_base, 0x01);
        parlcd_write_data(parlcd_mem_base, 0x02);
        parlcd_write_cmd(parlcd_mem_base, 0xC0);
        parlcd_write_data(parlcd_mem_base, 0x10);
        parlcd_write_data(parlcd_mem_base, 0x3B);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_data(parlcd_mem_base, 0x02);
        parlcd_write_data(parlcd_mem_base, 0x11);
        parlcd_write_cmd(parlcd_mem_base, 0xC5);
        parlcd_write_data(parlcd_mem_base, 0x08);
        parlcd_write_cmd(parlcd_mem_base, 0xC8);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_data(parlcd_mem_base, 0x32);
        parlcd_write_data(parlcd_mem_base, 0x36);
        parlcd_write_data(parlcd_mem_base, 0x45);
        parlcd_write_data(parlcd_mem_base, 0x06);
        parlcd_write_data(parlcd_mem_base, 0x16);
        parlcd_write_data(parlcd_mem_base, 0x37);
        parlcd_write_data(parlcd_mem_base, 0x75);
        parlcd_write_data(parlcd_mem_base, 0x77);
        parlcd_write_data(parlcd_mem_base, 0x54);
        parlcd_write_data(parlcd_mem_base, 0x0C);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_cmd(parlcd_mem_base, 0x36);
        parlcd_write_data(parlcd_mem_base, 0x0a);
        parlcd_write_cmd(parlcd_mem_base, 0x3A);
        parlcd_write_data(parlcd_mem_base, 0x55);
        parlcd_write_cmd(parlcd_mem_base, 0x2A);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_data(parlcd_mem_base, 0x01);
        parlcd_write_data(parlcd_mem_base, 0x3F);
        parlcd_write_cmd(parlcd_mem_base, 0x2B);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_data(parlcd_mem_base, 0x00);
        parlcd_write_data(parlcd_mem_base, 0x01);
        parlcd_write_data(parlcd_mem_base, 0xDF);
        parlcd_delay(120);
        parlcd_write_cmd(parlcd_mem_base, 0x29);
        parlcd_delay(25);
#else
// HX8357-C display initialisation
    parlcd_write_cmd(parlcd_mem_base, 0xB9); // Enable extension command
    parlcd_write_data(parlcd_mem_base, 0xFF);
    parlcd_write_data(parlcd_mem_base, 0x83);
    parlcd_write_data(parlcd_mem_base, 0x57);
    parlcd_delay(50);
    parlcd_write_cmd(parlcd_mem_base, 0xB6); //Set VCOM voltage
    //parlcd_write_data(parlcd_mem_base, 0x2C);    //0x52 for HSD 3.0"
    parlcd_write_data(parlcd_mem_base, 0x52);    //0x52 for HSD 3.0"
    parlcd_write_cmd(parlcd_mem_base, 0x11); // Sleep off
    parlcd_delay(200);
    parlcd_write_cmd(parlcd_mem_base, 0x35); // Tearing effect on
    parlcd_write_data(parlcd_mem_base, 0x00);    // Added parameter
    parlcd_write_cmd(parlcd_mem_base, 0x3A); // Interface pixel format
    parlcd_write_data(parlcd_mem_base, 0x55);    // 16 bits per pixel
    //parlcd_write_cmd(parlcd_mem_base, 0xCC); // Set panel characteristic
    //parlcd_write_data(parlcd_mem_base, 0x09);    // S960>S1, G1>G480, R-G-B, normally black
    //parlcd_write_cmd(parlcd_mem_base, 0xB3); // RGB interface
    //parlcd_write_data(parlcd_mem_base, 0x43);
    //parlcd_write_data(parlcd_mem_base, 0x00);
    //parlcd_write_data(parlcd_mem_base, 0x06);
    //parlcd_write_data(parlcd_mem_base, 0x06);
    parlcd_write_cmd(parlcd_mem_base, 0xB1); // Power control
    parlcd_write_data(parlcd_mem_base, 0x00);
    parlcd_write_data(parlcd_mem_base, 0x15);
    parlcd_write_data(parlcd_mem_base, 0x0D);
    parlcd_write_data(parlcd_mem_base, 0x0D);
    parlcd_write_data(parlcd_mem_base, 0x83);
    parlcd_write_data(parlcd_mem_base, 0x48);
    parlcd_write_cmd(parlcd_mem_base, 0xC0); // Does this do anything?
    parlcd_write_data(parlcd_mem_base, 0x24);
    parlcd_write_data(parlcd_mem_base, 0x24);
    parlcd_write_data(parlcd_mem_base, 0x01);
    parlcd_write_data(parlcd_mem_base, 0x3C);
    parlcd_write_data(parlcd_mem_base, 0xC8);
    parlcd_write_data(parlcd_mem_base, 0x08);
    parlcd_write_cmd(parlcd_mem_base, 0xB4); // Display cycle
    parlcd_write_data(parlcd_mem_base, 0x02);
    parlcd_write_data(parlcd_mem_base, 0x40);
    parlcd_write_data(parlcd_mem_base, 0x00);
    parlcd_write_data(parlcd_mem_base, 0x2A);
    parlcd_write_data(parlcd_mem_base, 0x2A);
    parlcd_write_data(parlcd_mem_base, 0x0D);
    parlcd_write_data(parlcd_mem_base, 0x4F);
    parlcd_write_cmd(parlcd_mem_base, 0xE0); // Gamma curve
    parlcd_write_data(parlcd_mem_base, 0x00);
    parlcd_write_data(parlcd_mem_base, 0x15);
    parlcd_write_data(parlcd_mem_base, 0x1D);
    parlcd_write_data(parlcd_mem_base, 0x2A);
    parlcd_write_data(parlcd_mem_base, 0x31);
    parlcd_write_data(parlcd_mem_base, 0x42);
    parlcd_write_data(parlcd_mem_base, 0x4C);
    parlcd_write_data(parlcd_mem_base, 0x53);
    parlcd_write_data(parlcd_mem_base, 0x45);
    parlcd_write_data(parlcd_mem_base, 0x40);
    parlcd_write_data(parlcd_mem_base, 0x3B);
    parlcd_write_data(parlcd_mem_base, 0x32);
    parlcd_write_data(parlcd_mem_base, 0x2E);
    parlcd_write_data(parlcd_mem_base, 0x28);
    parlcd_write_data(parlcd_mem_base, 0x24);
    parlcd_write_data(parlcd_mem_base, 0x03);
    parlcd_write_data(parlcd_mem_base, 0x00);
    parlcd_write_data(parlcd_mem_base, 0x15);
    parlcd_write_data(parlcd_mem_base, 0x1D);
    parlcd_write_data(parlcd_mem_base, 0x2A);
    parlcd_write_data(parlcd_mem_base, 0x31);
    parlcd_write_data(parlcd_mem_base, 0x42);
    parlcd_write_data(parlcd_mem_base, 0x4C);
    parlcd_write_data(parlcd_mem_base, 0x53);
    parlcd_write_data(parlcd_mem_base, 0x45);
    parlcd_write_data(parlcd_mem_base, 0x40);
    parlcd_write_data(parlcd_mem_base, 0x3B);
    parlcd_write_data(parlcd_mem_base, 0x32);
    parlcd_write_data(parlcd_mem_base, 0x2E);
    parlcd_write_data(parlcd_mem_base, 0x28);
    parlcd_write_data(parlcd_mem_base, 0x24);
    parlcd_write_data(parlcd_mem_base, 0x03);
    parlcd_write_data(parlcd_mem_base, 0x00);
    parlcd_write_data(parlcd_mem_base, 0x01);
    parlcd_write_cmd(parlcd_mem_base, 0x36); // MADCTL Memory access control
    //parlcd_write_data(parlcd_mem_base, 0x48);
    parlcd_write_data(parlcd_mem_base, 0xE8);
    parlcd_delay(20);
    parlcd_write_cmd(parlcd_mem_base, 0x21); //Display inversion on
    parlcd_delay(20);
    parlcd_write_cmd(parlcd_mem_base, 0x29); // Display on
    parlcd_delay(120);
#endif
}

void Drawer::AddRectangle(int x, int y, int width, int height, uint16_t color) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixels[y][x] = color;
        }
    }
}
