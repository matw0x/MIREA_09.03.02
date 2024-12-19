// Реализовать функцию sum, которая находит сумму для элементов
// массива как для типа int, так и для типа float, так и для типа string.
// Результатом суммы третьего массива должна быть конкатенация его
// элементов.

#include <iostream>
#include <string>
#include <numeric>

template <typename T>
T sum(T* container, const size_t& size) {
    return std::accumulate(container, container + size, T());
}

int main() {
    const size_t INTS_SIZE = 5;
    int ints[INTS_SIZE] = { 2, 3, 0, 5, -5 };
    std::cout << "INTEGER: " << sum(ints, INTS_SIZE) << std::endl;

    const size_t FLOATS_SIZE = 2;
    float floats[FLOATS_SIZE] = { 2.8, 1.1 };
    std::cout << "FLOAT: " << sum(floats, FLOATS_SIZE) << std::endl;

    const size_t STRINGS_SIZE = 3;
    std::string strings[STRINGS_SIZE] = { "hi", "hi", "kssss" };
    std::cout << "STRING: " << sum(strings, STRINGS_SIZE) << std::endl;

    return 0;
}