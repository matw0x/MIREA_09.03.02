#include <iostream>
#include <vector>

void merge(std::vector<int>& data, const int& start, const int& mid, const int& end) {
    std::vector<int> temp(end - start + 1);
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (data[i] <= data[j]) {
            temp[k++] = data[i++];
        } else {
            temp[k++] = data[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = data[i++];
    }

    while (j <= end) {
        temp[k++] = data[j++];
    }

    for (i = start, k = 0; i <= end; ++i, ++k) {
        data[i] = temp[k];
    }
}

void mergeSort(std::vector<int>& data, const int& start, const int& end) {
    if (start >= end) {
        return;
    }

    int mid = start + (end - start) / 2;

    mergeSort(data, start, mid); // left
    mergeSort(data, mid + 1, end); // right

    merge(data, start, mid, end);
}

void show(const std::vector<int>& data) {
    for (const auto& element : data) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {6, 7, 4, 5, 2, 0, 0, -1, 13};

    std::cout << "Before sort: ";
    show(arr);

    std::cout << "After sort: ";
    mergeSort(arr, 0, arr.size() - 1);
    show(arr);

    return 0;
}