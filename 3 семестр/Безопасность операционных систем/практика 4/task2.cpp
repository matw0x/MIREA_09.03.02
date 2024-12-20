#include <iostream>
#include <vector>

class PhysicalMemory {
public:
    PhysicalMemory(int totalPages) : totalPages(totalPages) {
        memory.resize(totalPages, 0);
    }

    int countFreePages() const {
        int freePages = 0;
        for (int page : memory) {
            if (page == 0) { 
                freePages++;
            }
        }
        return freePages;
    }

    bool allocatePage(int pageIndex) {
        if (pageIndex >= 0 && pageIndex < totalPages && memory[pageIndex] == 0) {
            memory[pageIndex] = 1;
            return true;
        }
        return false;
    }

    bool freePage(int pageIndex) {
        if (pageIndex >= 0 && pageIndex < totalPages && memory[pageIndex] == 1) {
            memory[pageIndex] = 0;
            return true;
        }
        return false;
    }

    int getTotalPages() const {
        return totalPages;
    }

private:
    int totalPages;
    std::vector<int> memory; // (0 - свободна, 1 - занята)
};

int main() {
    int totalPages;
    std::cout << "Введите общее количество страниц физической памяти: ";
    std::cin >> totalPages;

    PhysicalMemory memory(totalPages);
    
    memory.allocatePage(0);
    memory.allocatePage(1);

    std::cout << "Общее количество страниц: " << memory.getTotalPages() << std::endl;
    std::cout << "Количество свободных страниц: " << memory.countFreePages() << std::endl;

    memory.freePage(0);
    std::cout << "После освобождения страницы 0, количество свободных страниц: " 
              << memory.countFreePages() << std::endl;

    return 0;
}