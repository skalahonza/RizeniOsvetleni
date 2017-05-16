#include <iostream>
#include "Perifery.h"
#include "Line.h"
#include "Rectangle.h"
#include "TextBox.h"
#include "DisplayHandler.h"

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
}
void pressed2(){
    cout << "Green Pressed\n";
}
void pressed3(){
    cout << "Blue Pressed\n";
}

int main() {
    Color stroke = Color(255, 255, 255);

    Rectangle rectangle = Rectangle(stroke, 0, 280, 25, 39);
    TextBox tb = TextBox(100, 319 - 16, 200, 200, stroke);
    tb.setText_("Hello");

    DisplayHandler &handler = DisplayHandler::getInstance();
    handler.addShape(&rectangle);
    handler.addShape(&tb);
    handler.Refresh();

    Perifery controller = Perifery();
    controller.Register_R_Callback(test, "printer");
    controller.Register_G_Callback(test, "printer");
    controller.Register_B_Callback(test, "printer");

    controller.Register_R_Pressed_Callback(pressed1,"redclick");
    controller.Register_G_Pressed_Callback(pressed2,"greenclick");
    controller.Register_B_Pressed_Callback(pressed3,"blueclick");
    controller.Init();
    return 0;
}