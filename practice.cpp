#include <iostream>
#include "Array.h"

int main() {
    Array<int> arr(2);

    std::cout << arr << std::endl;

    arr.pushBack(10);
    arr.pushBack(30);
    arr.insertAt(1, 20);

    std::cout << arr << std::endl;

    arr.removeAt(1);
    std::cout << arr << std::endl;

    arr.clear();
    std::cout << arr << std::endl;
}