//
// Created by Jan Skála on 07.05.2017.
//

#ifndef UDPTASK_PERIFERY_H
#define UDPTASK_PERIFERY_H

#include <sys/types.h>
#include <vector>
#include <map>
#include "HardwareEndpoints.h"

enum SPINDIRECTION {
    UNCHANGED,
    LEFT,
    RIGHT
};

typedef void (*t_callback)(int);

class Perifery {
public:
    Perifery();

    void Init();

    void Register_R_Callback(t_callback callback, std::string key);

    void Register_G_Callback(t_callback callback, std::string key);

    void Register_B_Callback(t_callback callback, std::string key);

    void UnRegister_R_Callback(std::string key);

    void UnRegister_G_Callback(std::string key);

    void UnRegister_B_Callback(std::string key);

    void Clear_R_Callbacks();

    void Clear_G_Callbacks();

    void Clear_B_Callbacks();

    virtual ~Perifery();

private:
    void CheckLoop();

    void *map_phys_address(off_t region_base, size_t region_size, int opt_cached);

    void ResolveCallbacks(std::map<std::string, t_callback> callbacks, int value);

    void Resolve_R_Callbacks(int value);

    void Resolve_G_Callbacks(int value);

    void Resolve_B_Callbacks(int value);

    char SpinDirection(unsigned char previous, unsigned char current);

    char *memdev;
    volatile bool loop_;
    unsigned char red_, green_, blue_;
    std::map<std::string, t_callback> R_callbacks_;
    std::map<std::string, t_callback> G_callbacks_;
    std::map<std::string, t_callback> B_callbacks_;
};


#endif //UDPTASK_PERIFERY_H
