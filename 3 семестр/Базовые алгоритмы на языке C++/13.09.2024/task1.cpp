#include <iostream>

int main() {
    const int SIZE = 10;
    int** pArrays = new int*[SIZE];

    for (int i = 0; i != SIZE; ++i) {
        pArrays[i] = new int[i + 1];
    }

    for (int i = 0; i != SIZE; ++i) {
        for (int j = 0; j <= i; ++j) {
            int element = pArrays[i][j] = i + j;
            std::cout << element << ' ';
        }
        
        std::cout << '\n';
    }

    for (int i = 0; i != SIZE; ++i) {
        delete[] pArrays[i];
    }

    delete[] pArrays;

    return 0;
}
