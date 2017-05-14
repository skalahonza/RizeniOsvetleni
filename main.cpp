#include <iostream>
#include "Perifery.h"
#include "Line.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "Ellipse.h"
#include "TextBox.h"

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
    Color stroke = Color(0, 0, 1);

    Rectangle rectangle = Rectangle(stroke, 0, 280, 25, 39);
    //rectangle.Render(display);

    //Rectangle rectangle2 = Rectangle(80, 300, 120, 319, stroke);
    //rectangle2.Render(display);

    vector<Point> points = {
            Point(30, 319, stroke),
            Point(50, 319 - 20, stroke),
            Point(70, 319, stroke),
    };

    Polygon polygon = Polygon(points, stroke);
    //polygon.Render(display);

    Ellipse ellipse = Ellipse(160, 280, 50, 50, stroke);
    //ellipse.Render(display);

    TextBox tb = TextBox(0, 300, stroke, 200, 200);
    tb.setText_("Hello");
    tb.Render(display);

    for (int y = 0; y < 320; ++y) {
        for (int x = 0; x < 480; ++x) {
            cout << display[y][x];
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