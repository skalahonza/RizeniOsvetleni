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
    /**
     * Get singleton instance or create a new one
     * @return DisplayHandler singleton instance
     */
    static DisplayHandler &getInstance() {
        static DisplayHandler INSTANCE;
        return INSTANCE;
    }

    /**
     * Add shape into list, all shapes in the list will be rendered when Refresh() is called
     * @param shape Object that inherits from class Shape
     */
    void addShape(Shape *shape);

    /**
     * Remove all shapes from list and wipe all display
     */
    void clearDisplay();

    /**
     * Refresh display and (re)render all shapes on the display
     */
    void Refresh();
};


#endif //UDPTASK_DISPLAYHANDLER_H
