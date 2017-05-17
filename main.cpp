#include <iostream>
#include <sstream>
#include "Perifery.h"
#include "Line.h"
#include "TextBox.h"
#include "DisplayHandler.h"
#include "Rectangle.h"
#include "LightUnit.h"
#include "Broadcaster.h"
#include <stdio.h>

using namespace std;

void go_home();

void go_manage();

void select_unit();

void scroll_red_value(SPINDIRECTION a, int value);

void scroll_green_value(SPINDIRECTION a, int value);

void scroll_blue_value(SPINDIRECTION a, int value);

void scroll_attribute_list(SPINDIRECTION a, int value);

void update_textboxes();

void confirm_wall_managment();

void confirm_ceil_managment();

Rectangle *selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 28, 450,
                                               20);
unsigned int selectedIdx = 0; //selected index for listboxes

std::vector<LightUnit> units;
DisplayHandler &handler = DisplayHandler::getInstance();
Perifery controller = Perifery();
TextBox *unitsTb[10];

TextBox *r_value = new TextBox(13, 50, 200, 200, Color(255, 255, 255));
TextBox *g_value = new TextBox(102, 50, 200, 200, Color(255, 255, 255));
TextBox *b_value = new TextBox(192, 50, 200, 200, Color(255, 255, 255));

unsigned char r = 0, g = 0, b = 0;

LightUnit *examined_unit = NULL;

enum SETUP_MODE {
    WALL,
    CEIL
};

void scroll_unit_list(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0 || units.size() == 0) return;

    switch (a) {
        case LEFT:
            selectedIdx--;
            selectedIdx %= units.size();
            break;
        case RIGHT:
            selectedIdx++;
            selectedIdx %= units.size();
            break;
    }
    selection_rectangle->setY_(28 + selectedIdx * 20);
    selection_rectangle->setY2_(selection_rectangle->getY_() + 20);
    handler.Refresh();
}

void unit_management_screen(SETUP_MODE mode) {
    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    controller.Register_R_Callback(scroll_red_value, "scroll_attribute_list");
    controller.Register_G_Callback(scroll_green_value, "scroll_attribute_list");
    controller.Register_B_Callback(scroll_blue_value, "scroll_attribute_list");

    handler.clearDisplay();
    Color light_green = Color(152, 251, 152);
    TextBox *unitName_text = new TextBox(1, 1, 200, 200, light_green);
    unitName_text->setText_(examined_unit->getLabel_());
    handler.addShape(unitName_text);

    TextBox *changingName_text = new TextBox(1, 20, 200, 200, light_green);

    TextBox *r_text = new TextBox(1, 50, 200, 200, Color(255, 0, 0));
    r_text->setText_("R:");
    handler.addShape(r_text);


    TextBox *g_text = new TextBox(90, 50, 200, 200, Color(0, 255, 0));
    g_text->setText_("G:");
    handler.addShape(g_text);


    TextBox *b_text = new TextBox(180, 50, 200, 200, Color(0, 0, 255));
    b_text->setText_("B:");
    handler.addShape(b_text);


    stringstream streamr;
    stringstream streamg;
    stringstream streamb;

    switch (mode) {
        case WALL:
            changingName_text->setText_("Wall:");
            r = (unsigned char) examined_unit->getWall_().getRGB888().r;
            g = (unsigned char) examined_unit->getWall_().getRGB888().g;
            b = (unsigned char) examined_unit->getWall_().getRGB888().b;

            streamr << examined_unit->getWall_().getRGB888().r;
            streamg << examined_unit->getWall_().getRGB888().g;
            streamb << examined_unit->getWall_().getRGB888().b;

            controller.Register_G_Pressed_Callback(confirm_wall_managment, "confirm_wall_managment");
            break;
        case CEIL:
            changingName_text->setText_("Ceil:");

            r = (unsigned char) examined_unit->getCeil_().getRGB888().r;
            g = (unsigned char) examined_unit->getCeil_().getRGB888().g;
            b = (unsigned char) examined_unit->getCeil_().getRGB888().b;

            streamr << examined_unit->getCeil_().getRGB888().r;
            streamg << examined_unit->getCeil_().getRGB888().g;
            streamb << examined_unit->getCeil_().getRGB888().b;

            controller.Register_G_Pressed_Callback(confirm_ceil_managment, "confirm_ceil_managment");
            break;
    }
    r_value->setText_(streamr.str());
    g_value->setText_(streamg.str());
    b_value->setText_(streamb.str());
    handler.addShape(changingName_text);
    handler.addShape(r_value);
    handler.addShape(g_value);
    handler.addShape(b_value);
    handler.Refresh();
}

void unit_screen() {
    handler.clearDisplay();
    examined_unit = &units[selectedIdx];
    LightUnit &unit = *examined_unit;

    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    controller.Register_R_Callback(scroll_attribute_list, "scroll_attribute_list");
    controller.Register_G_Callback(scroll_attribute_list, "scroll_attribute_list");
    controller.Register_B_Callback(scroll_attribute_list, "scroll_attribute_list");

    controller.Register_G_Pressed_Callback(go_manage, "greenclick");

    Color light_green = Color(152, 251, 152);
    selectedIdx = 0;
    selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 50, 450,
                                        20);
    handler.addShape(selection_rectangle);

    TextBox *chooseChange_text = new TextBox(1, 1, 200, 200, light_green);
    chooseChange_text->setText_(unit.getLabel_());
    handler.addShape(chooseChange_text);

    TextBox *first_text = new TextBox(1, 30, 200, 200, light_green);
    first_text->setText_("CONFIGURE:");
    handler.addShape(first_text);

    TextBox *wallValue = new TextBox(1, 50, 200, 200, Color(255, 255, 255));
    stringstream stream;
    stream << "Wall color:  R: " << unit.getWall_().getRGB888().r << " G: " << unit.getWall_().getRGB888().g << " B: "
           << unit.getWall_().getRGB888().b;
    wallValue->setText_(stream.str());
    handler.addShape(wallValue);

    TextBox *ceilValue = new TextBox(1, 70, 200, 200, Color(255, 255, 255));
    stringstream stream2;
    stream2 << "Ceiling color:  R: " << unit.getCeil_().getRGB888().r << " G: " << unit.getCeil_().getRGB888().g
            << " B: "
            << unit.getCeil_().getRGB888().b;
    ceilValue->setText_(stream2.str());
    handler.addShape(ceilValue);

    TextBox *turn_offCeil = new TextBox(1, 90, 200, 200, Color(220, 220, 220));
    turn_offCeil->setText_("TURN OFF WALL");
    handler.addShape(turn_offCeil);

    TextBox *turn_offWall = new TextBox(1, 110, 200, 200, Color(220, 220, 220));
    turn_offWall->setText_("TURN OFF CEILING");
    handler.addShape(turn_offWall);
    handler.Refresh();

    TextBox *turn_onWall = new TextBox(1, 130, 200, 200, Color(150, 150, 150));
    turn_onWall->setText_("TURN ON WALL");
    handler.addShape(turn_onWall);

    TextBox *turn_onCeil = new TextBox(1, 150, 200, 200, Color(150, 150, 150));
    turn_onCeil->setText_("TURN ON CEILING");
    handler.addShape(turn_onCeil);
    handler.Refresh();
}

void home_screen() {
    selectedIdx = 0;
    handler.clearDisplay();

    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    controller.Register_R_Callback(scroll_unit_list, "printer");
    controller.Register_G_Callback(scroll_unit_list, "printer");
    controller.Register_B_Callback(scroll_unit_list, "printer");

    controller.Register_R_Pressed_Callback(go_home, "redclick");
    controller.Register_G_Pressed_Callback(select_unit, "greenclick");

    Color stroke = Color(255, 255, 255);
    Color light_green = Color(152, 251, 152);

    selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 28, 450,
                                        20);

    Line *green_line = new Line(0, 16, 115, 16, light_green);
    TextBox *first_text = new TextBox(1, 1, 200, 200, light_green);
    TextBox *use_text = new TextBox(1, 300, 200, 200, Color(255, 0, 0));
    first_text->setText_("LIGHT CONTROL:");
    use_text->setText_("Rotate the button, choose the device and confirm with press.");

    for (int i = 0; i < units.size(); ++i) {
        unitsTb[i] = new TextBox(1, i * 20 + 30, 200, 200, stroke);
        unitsTb[i]->setText_(units[i].debugString());
        handler.addShape((unitsTb[i]));
    }
    handler.addShape(first_text);
    handler.addShape(green_line);
    handler.addShape(selection_rectangle);
    handler.addShape(use_text);
    handler.Refresh();
}

void go_home() {
    home_screen();
}

void go_manage() {
    cout << selectedIdx << "\n";
    switch (selectedIdx) {
        case 0: //configure wall
            examined_unit = &units[selectedIdx];
            unit_management_screen(WALL);
            break;
        case 1: //configure ceiling
            examined_unit = &units[selectedIdx];
            unit_management_screen(CEIL);
            break;
    }
}

void select_unit() {
    unit_screen();
}

void scroll_attribute_list(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0 || units.size() == 0) return;

    switch (a) {
        case LEFT:
            selectedIdx--;
            selectedIdx %= 6;
            break;
        case RIGHT:
            selectedIdx++;
            selectedIdx %= 6;
            break;
    }

    selection_rectangle->setY_(50 + selectedIdx * 20);
    selection_rectangle->setY2_(selection_rectangle->getY_() + 20);
    handler.Refresh();
}

void scroll_red_value(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0) return;
    switch (a) {
        case LEFT:
            r--;
            break;
        case RIGHT:
            r++;
            break;
    }
    printf("r value: %d\n", r);
    update_textboxes();
}

void scroll_green_value(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0) return;
    switch (a) {
        case LEFT:
            g--;
            break;
        case RIGHT:
            g++;
            break;
    }
    printf("g value: %d\n", g);
    update_textboxes();
}

void scroll_blue_value(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0) return;
    switch (a) {
        case LEFT:
            b--;
            break;
        case RIGHT:
            b++;
            break;
    }
    printf("b value: %d\n", b);
    update_textboxes();
}

void update_textboxes() {
    stringstream streamr;
    stringstream streamg;
    stringstream streamb;

    streamr << (int) r;
    streamg << (int) g;
    streamb << (int) b;

    r_value->setText_(streamr.str());
    g_value->setText_(streamg.str());
    b_value->setText_(streamb.str());
    handler.Refresh();
}

void confirm_wall_managment() {
    examined_unit->setWall_(Color(r, g, b));
    examined_unit = NULL;
    home_screen();
}

void confirm_ceil_managment() {
    examined_unit->setCeil_(Color(r, g, b));
    examined_unit = NULL;
    home_screen();
}

int main(int argc, char *argv[]) {
    //MOCK LIGHT UNITS
    LightUnit host = LightUnit(1, "Living room");
    host.setCeil_(Color(100, 200, 30));
    host.setWall_(Color(10, 20, 30));
    host.setIsHost(true);

    LightUnit kitchen = LightUnit(2, "KItchen");
    kitchen.setCeil_(Color(11, 22, 33));
    kitchen.setWall_(Color(22, 33, 44));

    LightUnit bedroom = LightUnit(3, "bedroom");

    units.push_back(host);
    units.push_back(kitchen);
    units.push_back(bedroom);

    home_screen();

    //Broadcast daemon
    pid_t pid = fork();

    if (pid == 0) {
        while (true) {
            // child process
            cout << "broadcasting...\n";
            Broadcaster::getInstance().broadcastData(host);
            sleep(1);
        }
    }

    //listening thread

    controller.Init();
    return 0;
}