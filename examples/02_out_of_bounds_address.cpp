#include <iostream>

int main() {
    const auto size = 10;
    //int* dynamicArray = new int[size];
    int dynamicArray[size];
    for (int i = 0; i <= size; ++i) {
        *(dynamicArray + i) = i * 10;
    }

    std::cout << size << std::endl;

    //for (int i = 0; i <= size; ++i)
        //std::cout << i << " " << dynamicArray[i] << "; ";

    //delete[] dynamicArray;
}
