#include <iostream>
#include "Perifery.h"

using namespace std;

void test(int a) {
    cout << "Value is " << a << "\n";
}

int main() {
    Perifery controller = Perifery();
    controller.Register_R_Callback(test, "printer");
    controller.Init();
    return 0;
}