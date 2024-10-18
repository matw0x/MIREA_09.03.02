#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>

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

void bubbleSort(std::vector<int>& data) {
    for (size_t i = 0; i < data.size() - 1; ++i) {
        for (size_t j = 0; j < data.size() - i - 1; ++j) {
            if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);
        }
    }
}

int main() {
    std::ofstream file("result.txt");
    file << "Размер, теория, реальное" << "\n";

    srand(42);
    long double c = 0;

    for(int i = 1e3; i <= 1e4; i += 1e3) {
        file << i << ", ";

        std::vector<int> arr(i, 0);
        for (int j = 0; j < i; ++j) {
            arr[j] = rand();
        }

        double myTime = 0.0;
        for (int j = 0; j < 10; ++j) {
            double start = clock();
            bubbleSort(arr);
            double end = clock();

            myTime += end - start;
        }

        myTime /= 10;
        if (i == 1e3) {
            c = myTime / (long double)(i * i);
        }
        
        double ex = c * i * i;
        file << ex << ", " << myTime << std::endl;
    }

    file.close();

    return 0;
}