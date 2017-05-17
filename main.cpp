#include <iostream>
#include <sstream>
#include "Perifery.h"
#include "Line.h"
#include "TextBox.h"
#include "DisplayHandler.h"
#include "Rectangle.h"
#include "LightUnit.h"

using namespace std;

void go_home();

void select_unit();

Rectangle *selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 28, 450,
                                               20);
unsigned int selectedIdx = 0; //selected index for listboxes

std::vector<LightUnit> units;
DisplayHandler &handler = DisplayHandler::getInstance();
Perifery controller = Perifery();
TextBox *unitsTb[10];

void scroll_unit_list(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0 || units.size() == 0) return;

    switch (a) {
        case LEFT:
            cout << "Value: " << value << " LEFT \n";
            selectedIdx--;
            selectedIdx %= units.size();
            break;
        case RIGHT:
            cout << "Value: " << value << " RIGHT \n";
            selectedIdx++;
            selectedIdx %= units.size();
            break;
    }
    cout << selectedIdx << "\n";
    selection_rectangle->setY_(28 + selectedIdx * 20);
    selection_rectangle->setY2_(28 + selectedIdx * 20 + 20);
    handler.Refresh();
}

void scroll_attribute_list(SPINDIRECTION a, int value) {

}

void unit_screen(LightUnit unit) {
    handler.clearDisplay();
    controller.Clear_R_Callbacks();
    controller.Clear_G_Callbacks();
    controller.Clear_B_Callbacks();
    controller.Clear_G_Pressed_Callbacks();

    Color light_green = Color(152, 251, 152);

    TextBox *chooseChange_text = new TextBox(1, 1, 200, 200, light_green);
    chooseChange_text->setText_(unit.getLabel_());
    handler.addShape(chooseChange_text);

    TextBox *first_text = new TextBox(1, 30, 200, 200, light_green);
    first_text->setText_("CONFIGURE:");
    handler.addShape(first_text);


    TextBox *wallValue = new TextBox(1, 50, 200, 200, Color(255, 255, 255));
    stringstream stream;
    stream << "Wall color:  R: " << unit.getWall_().getRGB888().r << "G: " << unit.getWall_().getRGB888().g << "B: "
           << unit.getWall_().getRGB888().b;
    wallValue->setText_(stream.str());
    handler.addShape(wallValue);

    TextBox *ceilValue = new TextBox(1, 70, 200, 200, Color(255, 255, 255));
    stringstream stream2;
    stream2 << "Ceiling color:  R: " << unit.getCeil_().getRGB888().r << "G: " << unit.getCeil_().getRGB888().g << "B: "
            << unit.getCeil_().getRGB888().b;
    wallValue->setText_(stream.str());
    handler.addShape(ceilValue);

    selectedIdx = 1; //now choosing from 1,2
    handler.Refresh();
}


void home_screen() {
    units.clear();
    controller.Register_R_Callback(scroll_unit_list, "printer");
    controller.Register_G_Callback(scroll_unit_list, "printer");
    controller.Register_B_Callback(scroll_unit_list, "printer");

    controller.Register_R_Pressed_Callback(go_home, "redclick");
    controller.Register_G_Pressed_Callback(select_unit, "greenclick");

    Color stroke = Color(255, 255, 255);
    Color light_green = Color(152, 251, 152);

    units.push_back(LightUnit(1, "obyvak"));
    units.push_back(LightUnit(2, "kuchyn"));

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

void select_unit() {
    unit_screen(units[selectedIdx]);
}

int main() {
    home_screen();
    controller.Init();
    return 0;
}