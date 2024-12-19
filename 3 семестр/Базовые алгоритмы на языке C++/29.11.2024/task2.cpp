// Реализовать очередь из элементов класса Worker на основе
// односвязного списка.

#include <iostream>
#include <string>

enum Role {
    STUDENT,
    TEACHER,
    DIRECTOR
};

class Worker {
private:
    std::string firstName, lastName, patronymic;
    Role role;
    unsigned int salary;

    unsigned int maxSalary = 300000, defaultSalary = 20000;

public:
    void setFirstName(const std::string& fN) {
        firstName = fN;
    }

    void setLastName(const std::string& lN) {
        lastName = lN;
    }

    void setPatronymic(const std::string& p) {
        patronymic = p;
    }

    void setRole(const Role& r) {
        role = r;
    }

    void setSalary(const unsigned int& s) {
        if (s > maxSalary) {
            std::cout << "Bussines rule: error! Setted default value.\n";
            salary = defaultSalary;
        } else {
            salary = s;
        }
    }

    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    std::string getPatronymic() const { return patronymic; }
    Role getRole() const { return role; }
    unsigned int getSalary() const { return salary; }

    void print() const {
        std::cout << firstName << ' ' << lastName << ' ' << patronymic << std::endl;
        std::cout << "Salary: " << salary << " | Role: ";

        switch (role) {
            case STUDENT:
                std::cout << "Student";
                break;
            case TEACHER:
                std::cout << "Teacher";
                break;
            case DIRECTOR:
                std::cout << "Director";
                break;
            default:
                std::cout << "Imposter :)";
                break;
        }

        std::cout << "\n\n";
    }
};

class Queue {
private:
    struct Node {
        Worker data;
        Node* next;

        Node(const Worker& worker) : data(worker), next(nullptr) {}
    };

    Node* head;

public:
    Queue() : head(nullptr) {}
    ~Queue() { while (!isEmpty()) dequeue(); }

    bool isEmpty() const { return !head; }

    void push(const Worker& worker) {
        Node* newNode = new Node(worker);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    void dequeue() {
        if (head == nullptr) {
            std::cout << "Queue is empty!\n";
            return;
        }

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void print() const {
        if (isEmpty()) {
            std::cout << "Queue is empty!\n";
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            current->data.print();
            current = current->next;
        }
    }
};

int main() {
    Worker worker1, worker2, worker3;
    worker1.setFirstName("Ryan");
    worker1.setLastName("Gosling");
    worker1.setPatronymic("Thomas");
    worker1.setRole(TEACHER);
    worker1.setSalary(28000);

    worker2.setFirstName("Jason");
    worker2.setLastName("Statham");
    worker2.setPatronymic("Michael");
    worker2.setRole(STUDENT);
    worker2.setSalary(15000);

    worker3.setFirstName("Walter");
    worker3.setLastName("White");
    worker3.setPatronymic("Hartwell");
    worker3.setRole(DIRECTOR);
    worker3.setSalary(300000);

    Queue q;
    q.push(worker1);
    q.push(worker2);
    q.push(worker3);

    q.print();

    return 0;
}