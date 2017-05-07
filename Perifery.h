//
// Created by Jan Skála on 07.05.2017.
//

#ifndef UDPTASK_PERIFERY_H
#define UDPTASK_PERIFERY_H

#include <sys/types.h>

class Perifery {
public:
    Perifery();
    ~Perifery();

private:
    void CheckLoop();
    void *map_phys_address(off_t region_base, size_t region_size, int opt_cached);
    char *memdev;
};


#endif //UDPTASK_PERIFERY_H
