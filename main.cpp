#include <iostream>
#include "Perifery.h"

using namespace std;

void test(SPINDIRECTION a) {
    switch (a) {
        case UNCHANGED:
            cout << "Unchanged \n";
            break;
        case LEFT:
            cout << "LEFT \n";
            break;
        case RIGHT:
            cout << "RIGHT \n";
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