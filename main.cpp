#include <iostream>
#include "Perifery.h"
#include "Line.h"
#include "TextBox.h"
#include "DisplayHandler.h"
#include "LightUnit.h"

using namespace std;

void test(SPINDIRECTION a, int value) {
    switch (a) {
        case LEFT:
            cout << "Value: " << value <<  " LEFT \n";
            break;
        case RIGHT:
            cout << "Value: " << value <<  " RIGHT \n";
            break;
    }
}

void pressed1(){
    cout << "Red Pressed\n";
    DisplayHandler::getInstance().clearDisplay();
}
void pressed2(){
    cout << "Green Pressed\n";
}
void pressed3(){
    cout << "Blue Pressed\n";
}

int main() {
    Color stroke = Color(255, 255, 255);
    Color light_green = Color(152, 251, 152);
    DisplayHandler &handler = DisplayHandler::getInstance();
    TextBox unitsTb[10];


    std::vector<LightUnit> units;
    units.push_back(LightUnit(1, "obyvak"));
    units.push_back(LightUnit(2, "kuchyn"));

    Line green_line = Line(0, 16, 115, 16, light_green);
    TextBox first_text = TextBox(1, 1, 200, 200, light_green);
    first_text.setText_("Light Control:");

    for (int i = 0; i < units.size(); ++i) {
        unitsTb[i] = TextBox(1, i * 20 + 20, 200, 200, stroke);
        unitsTb[i].setText_(units[i].debugString());
        handler.addShape(&(unitsTb[i]));

        //create textboxes
        //units[i]
        //add to display
    }
    //

    //Rectangle rectangle = Rectangle(stroke, 0, 280, 25, 39);
    // TextBox tb = TextBox(100, 319 - 16, 200, 200, stroke);
    //tb.setText_("Hello");

    handler.addShape(&first_text);
    handler.addShape(&green_line);
    //handler.addShape(&rectangle);
    //handler.addShape(&tb);

    handler.Refresh();


    Perifery controller = Perifery();
    controller.Register_R_Callback(test, "printer");
    controller.Register_G_Callback(test, "printer");
    controller.Register_B_Callback(test, "printer");

    //controller.UnRegister_R_Callback("printer"); smaže toho který se jemnuje printer
    //controller.Clear_R_Callbacks(); smaže všechny

    controller.Register_R_Pressed_Callback(pressed1,"redclick");
    controller.Register_G_Pressed_Callback(pressed2,"greenclick");
    controller.Register_B_Pressed_Callback(pressed3,"blueclick");
    controller.Init();
    return 0;
}