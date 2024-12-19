// Реализовать однонаправленный список с данными типа T для каждого
// элемента. T может быть int, double и string.

#include <iostream>
#include <iostream>

template <typename T>
class MyList {
private:
    struct Node {
        T info;
        Node* next;

        Node(const T& value) : info(value), next(nullptr) {}
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

    void add(const T& x) {
        Node* newNode = new Node(x);

        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }

            current->next = newNode;
        }
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
    MyList<int> integers;
    integers.add(1);
    integers.add(0);
    integers.add(2);
    integers.add(3);
    integers.add(5);
    std::cout << "INTEGERS: "; integers.show();

    MyList<double> doubles;
    doubles.add(1.5);
    doubles.add(0.0);
    doubles.add(2.2);
    doubles.add(5.1);
    std::cout << "DOUBLES: "; doubles.show();

    MyList<std::string> strings;
    strings.add("HARD");
    strings.add("STYLE");
    strings.add("ZYZZ");
    std::cout << "STRINGS: "; strings.show();

    return 0;
}