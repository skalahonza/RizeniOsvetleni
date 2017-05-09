//
// Created by Jan Skála on 07.05.2017.
//

#ifndef UDPTASK_PERIFERY_H
#define UDPTASK_PERIFERY_H

#include <sys/types.h>
#include <vector>
#include <functional>
#include <map>
#include "HardwareEndpoints.h"

class Perifery {
public:
    Perifery();

    void Register_R_Callback(std::function<void(int)> callback, std::string key);

    void Register_G_Callback(std::function<void(int)> callback, std::string key);

    void Register_B_Callback(std::function<void(int)> callback, std::string key);

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

    void ResolveCallbacks(std::map<std::string, std::function<void(int)>> callbacks, int value);

    void Resolve_R_Callbacks(int value);

    void Resolve_G_Callbacks(int value);

    void Resolve_B_Callbacks(int value);

    char SpinDirection(unsigned char previous, unsigned char current);

    char *memdev;
    volatile bool loop_ = true;
    unsigned char red_, green_, blue_;
    std::map<std::string, std::function<void(int)>> R_callbacks_;
    std::map<std::string, std::function<void(int)>> G_callbacks_;
    std::map<std::string, std::function<void(int)>> B_callbacks_;
};


#endif //UDPTASK_PERIFERY_H
