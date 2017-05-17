#include <iostream>
#include "Perifery.h"
#include "Line.h"
#include "TextBox.h"
#include "DisplayHandler.h"
#include "Rectangle.h"
#include "LightUnit.h"

using namespace std;

Rectangle *selection_rectangle;
unsigned int selectedIdx = 0; //(1-list_index), max. 10, min 1
unsigned int mode = 1; //mode 1,2,3 - which screen do I have

std::vector<LightUnit> units;
DisplayHandler &handler = DisplayHandler::getInstance();
TextBox unitsTb[10];

void test(SPINDIRECTION a, int value) {
    //ignore small steps
    if (value % 4 != 0 || units.size() == 0) return;

    switch (a) {
        case LEFT:
            cout << "Value: " << value <<  " LEFT \n";
            selectedIdx--;
            selectedIdx %= units.size();
            break;
        case RIGHT:
            cout << "Value: " << value <<  " RIGHT \n";
            selectedIdx++;
            selectedIdx %= units.size();
            break;
    }
    cout << selectedIdx << "\n";
    selection_rectangle->setY_(28 + selectedIdx * 20);
    selection_rectangle->setY2_(28 + selectedIdx * 20);
    handler.Refresh();
}

void choosing_screen() {
    handler.clearDisplay();
    Color light_green = Color(152, 251, 152);
    TextBox chooseChange_text = TextBox(1, 1, 200, 200, light_green);
    chooseChange_text.setText_("CHOOSE WHAT DO YOU WANT TO CHANGE:");
    TextBox ceiling = TextBox(1, 30, 200, 200, Color(255, 0, 0));
    TextBox wall = TextBox(1, 50, 200, 200, Color(255, 0, 0));
    ceiling.setText_("Ceiling");
    wall.setText_("Walls");
    //selection_rectangle = Rectangle(Color(255, 255, 255), 0, 28, 450, 20);
    handler.addShape(&chooseChange_text);
    handler.addShape(&ceiling);
    handler.addShape(&wall);
    //handler.addShape(&selection_rectangle);
    mode = 2;
    selectedIdx = 1; //now choosing from 1,2
    handler.Refresh();

}


void home_screen() { //originally in main
    Color stroke = Color(255, 255, 255);
    Color light_green = Color(152, 251, 152);
    selection_rectangle = new Rectangle(Color(255, 255, 255), 0, 28, 450,
                                        20);

    units.push_back(LightUnit(1, "obyvak"));
    units.push_back(LightUnit(2, "kuchyn"));

    Line *green_line = new Line(0, 16, 115, 16, light_green);
    TextBox *first_text = new TextBox(1, 1, 200, 200, light_green);
    TextBox *use_text = new TextBox(1, 300, 200, 200, Color(255, 0, 0));
    first_text->setText_("LIGHT CONTROL:");
    use_text->setText_("Rotate the button, choose the device and confirm with press.");

    for (int i = 0; i < units.size(); ++i) {
        unitsTb[i] = TextBox(1, i * 20 + 30, 200, 200, stroke);
        unitsTb[i].setText_(units[i].debugString());
        handler.addShape(&(unitsTb[i]));
    }
    handler.addShape(first_text);
    handler.addShape(green_line);
    handler.addShape(selection_rectangle);
    handler.addShape(use_text);
    mode = 1;
    handler.Refresh();
}


void pressed1() {
    cout << "Red Pressed\n";
    handler.clearDisplay();
}

void pressed2() {
    cout << "Green Pressed\n"; //only this button can confirm now
    if (mode == 1) {
        choosing_screen();
    }
}

void pressed3() {
    cout << "Blue Pressed\n";
}


int main() {
    home_screen();

    Perifery controller = Perifery();
    controller.Register_R_Callback(test, "printer");
    controller.Register_G_Callback(test, "printer");
    controller.Register_B_Callback(test, "printer");

    controller.Register_R_Pressed_Callback(pressed1, "redclick");
    controller.Register_G_Pressed_Callback(pressed2, "greenclick");
    controller.Register_B_Pressed_Callback(pressed3,"blueclick");
    controller.Init();
    return 0;
}