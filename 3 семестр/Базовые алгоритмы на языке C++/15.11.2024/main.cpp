// Реализовать класс MyList, представляющий собой однонаправленный
// список элементов, каждый из которых является структурой, состоящей
// из двух полей: уникальной информации (целого числа) и указателя на
// следующий элемент. Класс должен содержать конструктор, методы:
// add(x) - добавить элемент в список. Добавляет элемент в список по
// возрастанию поля с информацией. Предусмотреть возможность
// добавления в начало, в середину и внутрь списка. delete(x) - удалить
// элемент со значением x. Также предусмотреть три возможных места
// удаления. get(n) - выдать информацию элемента с номером n. show() -
// печать значений всех информационных полей.

#include <iostream>

class MyList {
private:
    struct Node {
        int info;
        Node* next;

        Node(const int& value) : info(value), next(nullptr) {}
    };

    Node* head;
    
public:
    MyList() : head(nullptr) {}
    ~MyList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void add(const int& x) {
        Node* newNode = new Node(x);

        if (!head || x < head->info) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && current->next->info < x) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }

    void delete_(const int& x) {
        if (!head) {
            std::cout << "List is empty, cannot delete " << x << "\n";
            return;
        }

        if (head->info == x) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        while (current->next && current->next->info != x) {
            current = current->next;
        }

        if (!current->next) {
            std::cout << "Element " << x << " not found in the list.\n";
            return;
        }

        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    int get(const int& n) const {
        if (n < 0) {
            std::cout << "Invalid index: " << n << ".\n";
            return -1;
        }

        Node* current = head;
        int index = 0;

        while (current) {
            if (index == n) {
                return current->info;
            }

            current = current->next;
            ++index;
        }

        std::cout << "Index " << n << " is out of bounds.\n";
        return -1;
    }

    void show() const {
        Node* current = head;

        if (!current) {
            std::cout << "List is empty.\n";
            return;
        }

        while (current) {
            std::cout << current->info << " -> ";
            current = current->next;
        }

        std::cout << "nullptr\n";
    }

};

int main() {
    MyList list;

    list.add(1);
    list.add(5);
    list.add(22);
    list.add(15);

    std::cout << "Initial list:\n";
    list.show();

    std::cout << "\nDelete 5:\n";
    list.delete_(5);
    list.show();

    std::cout << "\nGet element at index 1:\n";
    int value = list.get(1);
    if (value != -1) {
        std::cout << "Element at index 1: " << value << '\n';
    }

    std::cout << "\nDelete 30 (non-existent):\n";
    list.delete_(30);
    list.show();

    std::cout << "\nFinal list:\n";
    list.show();

    return 0;
}