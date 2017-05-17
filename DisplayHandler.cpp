//
// Created by skala on 16.5.17.
//

#include <cstring>
#include "DisplayHandler.h"
#include "Perifery.h"

DisplayHandler::DisplayHandler() {
    //Init display
    Perifery controller = Perifery();
    parlcd_mem_base_ = (unsigned char *) controller.map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    memset(display, 0, sizeof(display[0][0]) * 320 * 480);
}

void DisplayHandler::addShape(Shape *shape) {
    shapes_.push_back(shape);
}

void DisplayHandler::Refresh() {
    //CLean display
    clear_display();

    //Render all shapes
    for (int i = 0; i < shapes_.size(); ++i) {
        shapes_[i]->Render(display);
    }

    for (int y = 0; y < 320; ++y) {
        for (int x = 0; x < 480; ++x) {
            parlcd_write_data(display[y][x]);
        }
    }
}

void DisplayHandler::parlcd_write_data(int16_t data) {
    *(volatile uint16_t *) (parlcd_mem_base_ + PARLCD_REG_DATA_o) = (uint16_t) data;
}

void DisplayHandler::parlcd_write_cmd(int16_t cmd) {
    *(volatile uint16_t *) (parlcd_mem_base_ + PARLCD_REG_CMD_o) = (uint16_t) cmd;
}

void DisplayHandler::clear_display() {
    // move to beginning
    parlcd_write_cmd(0x2c);
    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 480; j++) {
            parlcd_write_data(0);
        }
    }
    parlcd_write_cmd(0x2c);
}

void DisplayHandler::clearDisplay() {
    shapes_.clear();
    Refresh();
}


