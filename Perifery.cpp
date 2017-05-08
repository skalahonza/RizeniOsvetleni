//
// Created by Jan Skála on 07.05.2017.
//

#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include "Perifery.h"


/*
 * The support function which returns pointer to the virtual
 * address at which starts remapped physical region in the
 * process virtual memory space.
 */
void *Perifery::map_phys_address(off_t region_base, size_t region_size, int opt_cached) {
    unsigned long mem_window_size;
    unsigned long pagesize;
    unsigned char *mm;
    unsigned char *mem;
    int fd;

    /*
     * Open a device ("/dev/mem") representing physical address space
     * in POSIX systems
     */
    fd = open(memdev, O_RDWR | (!opt_cached ? O_SYNC : 0));
    if (fd < 0) {
        fprintf(stderr, "cannot open %s\n", memdev);
        return NULL;
    }

    /*
     * The virtual to physical address mapping translation granularity
     * corresponds to memory page size. This call obtains the page
     * size used by running operating system at given CPU architecture.
     * 4kB are used by Linux running on ARM, ARM64, x86 and x86_64 systems.
     */
    pagesize = sysconf(_SC_PAGESIZE);

    /*
     * Extend physical region start address and size to page size boundaries
     * to cover complete requested region.
     */
    mem_window_size = ((region_base & (pagesize - 1)) + region_size + pagesize - 1) & ~(pagesize - 1);

    /*
     * Map file (in our case physical memory) range at specified offset
     * to virtual memory ragion/area (see VMA Linux kernel structures)
     * of the process.
     */
    mm = (unsigned char *) mmap(NULL, mem_window_size, PROT_WRITE | PROT_READ,
                                MAP_SHARED, fd, region_base & ~(pagesize - 1));

    /* Report failure if the mmap is not allowed for given file or its region */
    if (mm == MAP_FAILED) {
        fprintf(stderr, "mmap error\n");
        return NULL;
    }

    /*
     * Add offset in the page to the returned pointer for non-page-aligned
     * requests.
     */
    mem = mm + (region_base & (pagesize - 1));

    return mem;
}

Perifery::Perifery() {
    memdev = (char *) "/dev/mem";
    CheckLoop();
}

Perifery::~Perifery() {
}

void Perifery::CheckLoop() {

    unsigned char *mem_base;

    /*
     * Setup memory mapping which provides access to the peripheral
     * registers region of RGB LEDs, knobs and line of yellow LEDs.
     */
    mem_base = (unsigned char *) map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);

    if (mem_base == NULL) {
        //Error
        std::cerr << "Error during perifery address initialization.\n";
        return;
    }
    uint32_t rgb_knobs_value_previous = 0;
    while (loop_) {
        uint32_t rgb_knobs_value;
        int int_val;
        unsigned int uint_val;

        /* Initialize structure to 0 seconds and 200 milliseconds */
        struct timespec loop_delay = {.tv_sec = 0, .tv_nsec = 200 * 1000 * 1000};

        /*
         * Access register holding 8 bit relative knobs position
         * The type "(volatile uint32_t*)" casts address obtained
         * as a sum of base address and register offset to the
         * pointer type which target in memory type is 32-bit unsigned
         * integer. The "volatile" keyword ensures that compiler
         * cannot reuse previously read value of the location.
         */
        rgb_knobs_value = *(volatile uint32_t *) (mem_base + SPILED_REG_KNOBS_8BIT_o);

        //No change detected
        if (rgb_knobs_value_previous == rgb_knobs_value)
            continue;

        /* Store the read value to the register controlling individual LEDs */
        *(volatile uint32_t *) (mem_base + SPILED_REG_LED_LINE_o) = rgb_knobs_value;

        /*
         * Store RGB knobs values to the corersponding components controlling
         * a color/brightness of the RGB LEDs
         */
        *(volatile uint32_t *) (mem_base + SPILED_REG_LED_RGB1_o) = rgb_knobs_value;

        *(volatile uint32_t *) (mem_base + SPILED_REG_LED_RGB2_o) = rgb_knobs_value;

        /* Assign value read from knobs to the basic signed and unsigned types */
        int_val = rgb_knobs_value;
        uint_val = rgb_knobs_value;

        /* Print values */
        printf("int %10d uint 0x%08x\n", int_val, uint_val);

        /*
         * Wait for time specified by "loop_delay" variable.
         * Use monotonic clocks as time reference to ensure
         * that wait interval is not prolonged or shortened
         * due to real time adjustment.
         */
        clock_nanosleep(CLOCK_MONOTONIC, 0, &loop_delay, NULL);
    }
}

