#include <iostream>
#include "Perifery.h"

using namespace std;

void test(SPINDIRECTION a, int value) {
    switch (a) {
        case UNCHANGED:
            cout << "Value: " << value << " Unchanged \n";
            break;
        case LEFT:
            cout << "Value: " << value <<  " LEFT \n";
            break;
        case RIGHT:
            cout << "Value: " << value <<  " RIGHT \n";
            break;
    }
}

int main() {
    Perifery controller = Perifery();
    controller.Register_R_Callback(test, "printer");
    controller.Register_G_Callback(test, "printer");
    controller.Register_B_Callback(test, "printer");
    controller.Init();
    return 0;
}