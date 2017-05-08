#include <iostream>
#include "Perifery.h"

using namespace std;

void test(int a) {
    cout << "Value is " << a << "\n";
}

int main() {
    cout << "Infinite loop\n";
    auto controller = Perifery();
    controller.Register_R_Callback(test);
    return 0;
}