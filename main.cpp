#include <iostream>
#include "Perifery.h"
#include "Line.h"
#include "TextBox.h"
#include "DisplayHandler.h"
#include "Rectangle.h"
#include "LightUnit.h"

using namespace std;

Rectangle rectangle = Rectangle(Color(255, 255, 255), 0, 28, 450,
                                20); //LZE TO TAKTO DEKLAROVAT?? a prepise se to, tak jak chci?
unsigned int chosen_id; //(1-list_index), max. 10, min 1
unsigned int list_size = 1; // need to get vector size
unsigned int mode = 1; //mode 1,2,3 - which screen do I have
DisplayHandler &handler = DisplayHandler::getInstance();

void test(SPINDIRECTION a, int value) {
    switch (a) {
        case LEFT:
            cout << "Value: " << value <<  " LEFT \n";
            if ((mode == 1) & (chosen_id > 1)) {
                chosen_id--;
                rectangle = Rectangle(Color(255, 255, 255), 0, 28 + (chosen_id - 1) * 20, 450, 20);
                handler.Refresh();
            }
            if ((mode == 2) & (chosen_id > 1)) {
                chosen_id--;
                rectangle = Rectangle(Color(255, 255, 255), 0, 28 + (chosen_id - 1) * 20, 450,
                                      20); //only 28 should be ok
                handler.Refresh();
            }
            break;
        case RIGHT:
            cout << "Value: " << value <<  " RIGHT \n";
            if ((mode == 1) & (chosen_id < list_size)) {
                chosen_id++;
                rectangle = Rectangle(Color(255, 255, 255), 0, 28 + (chosen_id - 1) * 20, 450, 20);
                handler.Refresh();
            }
            if ((mode == 2) & (chosen_id < 2)) {
                chosen_id++;
                rectangle = Rectangle(Color(255, 255, 255), 0, 28 + (chosen_id - 1) * 20, 450, 20);
                handler.Refresh();
            }
            break;
    }
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
    rectangle = Rectangle(Color(255, 255, 255), 0, 28, 450, 20);
    handler.addShape(&chooseChange_text);
    handler.addShape(&ceiling);
    handler.addShape(&wall);
    handler.addShape(&rectangle);
    mode = 2;
    chosen_id = 1; //now choosing from 1,2
    handler.Refresh();

}


void home_screen() { //originally in main
    Color stroke = Color(255, 255, 255);
    Color light_green = Color(152, 251, 152);
    TextBox unitsTb[10];

    //need to get the service_list
    std::vector<LightUnit> units;
    units.push_back(LightUnit(1, "obyvak"));
    units.push_back(LightUnit(2, "kuchyn"));
    list_size = units.size();

    Line green_line = Line(0, 16, 115, 16, light_green);
    TextBox first_text = TextBox(1, 1, 200, 200, light_green);
    TextBox use_text = TextBox(1, 300, 200, 200, Color(255, 0, 0));
    first_text.setText_("LIGHT CONTROL:");
    use_text.setText_("Rotate the button, choose the device and confirm with press.");

    for (int i = 0; i < units.size(); ++i) {
        unitsTb[i] = TextBox(1, i * 20 + 30, 200, 200, stroke);
        unitsTb[i].setText_(units[i].debugString());
        handler.addShape(&(unitsTb[i]));
    }
    handler.addShape(&first_text);
    handler.addShape(&green_line);
    handler.addShape(&rectangle);
    handler.addShape(&use_text);
    mode = 1;
    handler.Refresh();
}


void pressed1() {
    cout << "Red Pressed\n";
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

    //controller.UnRegister_R_Callback("printer"); smaže toho který se jemnuje printer
    //controller.Clear_R_Callbacks(); smaže všechny

    controller.Register_R_Pressed_Callback(pressed1, "redclick");
    controller.Register_G_Pressed_Callback(pressed2, "greenclick");
    controller.Register_B_Pressed_Callback(pressed3,"blueclick");
    controller.Init();
    return 0;
}