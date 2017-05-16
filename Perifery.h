//
// Created by Jan Skála on 07.05.2017.
//

#ifndef UDPTASK_PERIFERY_H
#define UDPTASK_PERIFERY_H

#include <sys/types.h>
#include <vector>
#include <map>
#include <string>
#include "HardwareEndpoints.h"
#include <inttypes.h>

enum SPINDIRECTION {
    UNCHANGED,
    LEFT,
    RIGHT
};

typedef void (*t_callback)(SPINDIRECTION,int);
typedef void (*t_pressed_callback)();

class Perifery {
public:
    Perifery();

    void Init();

    void Register_R_Callback(t_callback callback, std::string key);

    void Register_G_Callback(t_callback callback, std::string key);

    void Register_B_Callback(t_callback callback, std::string key);

    void Register_R_Pressed_Callback(t_pressed_callback callback, std::string key);
    void Register_G_Pressed_Callback(t_pressed_callback callback, std::string key);
    void Register_B_Pressed_Callback(t_pressed_callback callback, std::string key);

    void UnRegister_R_Callback(std::string key);

    void UnRegister_G_Callback(std::string key);

    void UnRegister_B_Callback(std::string key);

    void UnRegister_R_Pressed_Callback(std::string key);

    void UnRegister_G_Pressed_Callback(std::string key);

    void UnRegister_B_Pressed_Callback(std::string key);

    void Clear_R_Callbacks();

    void Clear_G_Callbacks();

    void Clear_B_Callbacks();

    void Clear_R_Pressed_Callbacks();

    void Clear_G_Pressed_Callbacks();

    void Clear_B_Pressed_Callbacks();

    void *map_phys_address(off_t region_base, size_t region_size, int opt_cached);

    virtual ~Perifery();

private:
    void CheckLoop();

    void ResolveCallbacks(std::map<std::string, t_callback> callbacks, SPINDIRECTION direction, int value);

    void Resolve_R_Callbacks(SPINDIRECTION direction, int value) ;

    void Resolve_G_Callbacks(SPINDIRECTION direction, int value) ;

    void Resolve_B_Callbacks(SPINDIRECTION direction, int value) ;

    void Resolve_R_Pressed_Callbacks();
    void Resolve_G_Pressed_Callbacks();
    void Resolve_B_Pressed_Callbacks();
    void ResolvePressedCallbacks(std::map<std::string, t_pressed_callback > callbacks);

    SPINDIRECTION SpinDirection(unsigned char previous, unsigned char current);

    unsigned char *mem_base_;
    char *memdev;
    volatile bool loop_;
    unsigned char red_, green_, blue_;
    std::map<std::string, t_callback> R_callbacks_;
    std::map<std::string, t_callback> G_callbacks_;
    std::map<std::string, t_callback> B_callbacks_;
    std::map<std::string, t_pressed_callback> R_pressed_callbacks_;
    std::map<std::string, t_pressed_callback> G_pressed_callbacks_;
    std::map<std::string, t_pressed_callback> B_pressed_callbacks_;
};


#endif //UDPTASK_PERIFERY_H
