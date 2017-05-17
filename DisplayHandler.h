//
// Created by skala on 16.5.17.
//

#ifndef UDPTASK_DISPLAYHANDLER_H
#define UDPTASK_DISPLAYHANDLER_H

#include <vector>
#include "Shape.h"

#define PARLCD_REG_BASE_PHYS 0x43c00000
#define PARLCD_REG_SIZE      0x00004000
#define PARLCD_REG_DATA_o    0x000C
#define PARLCD_REG_CMD_o     0x0008


class DisplayHandler {
private:
    DisplayHandler();

    DisplayHandler(DisplayHandler const &); // Don't Implement
    void operator=(DisplayHandler const &); // Don't implement
    unsigned char *parlcd_mem_base_;
    int16_t display[320][480];
    std::vector<Shape *> shapes_;

    void parlcd_write_data(int16_t data);

    void parlcd_write_cmd(int16_t cmd);

public:
    static DisplayHandler &getInstance() {
        static DisplayHandler INSTANCE;
        return INSTANCE;
    }

    void addShape(Shape *shape);

    void clearDisplay();
    void Refresh();


};


#endif //UDPTASK_DISPLAYHANDLER_H