#include <iostream>
#include <algorithm>
#include <vector>

void bubbleSort(std::vector<int>& data) {
    for (size_t i = 0; i < data.size() - 1; ++i) {
        for (size_t j = 0; j < data.size() - i - 1; ++j) {
            if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);
        }
    }
}

void show(const std::vector<int>& data) {
    for (auto const& element : data) {
        std::cout << element << ' ';
    }
    
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {6, 7, 4, 5, 2, 0, 0, -1, 13};
    std::cout << "Before sort: ";
    show(arr);

    std::cout << "After sort: ";
    bubbleSort(arr);
    show(arr);

    return 0;
}