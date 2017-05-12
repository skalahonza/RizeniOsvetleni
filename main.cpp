#include <iostream>
#include "Perifery.h"
#include "Line.h"
#include "Point.h"

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
    int16_t display[320][480] = {0};
    Color stroke = Color(35, 35, 35);
    Line line = Line(50, 319, 25, 319 - 50, stroke);
    line.Render(display);

    Point point = Point(0, 319, stroke);
    point.Render(display);

    for (int y = 0; y < 320; ++y) {
        for (int x = 0; x < 480; ++x) {
            printf("%d", display[y][x]);
        }
        cout << "\n";
    }

    return 0;
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