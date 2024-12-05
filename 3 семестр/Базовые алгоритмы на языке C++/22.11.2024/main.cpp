// Реализовать стек из элементов класса Worker на основе односвязного
// списка. Поместить в стек трех воркеров, достать их из стека и вывести
// на экран.

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

class Stack {
private:
    struct Node {
        Worker data;
        Node* next;

        Node(const Worker& w, Node* n = nullptr) : data(w), next(n) {}
    };

    Node* head;

public:
    Stack() : head(nullptr) {}

    ~Stack() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const Worker& worker) {
        Node* newNode = new Node(worker, head);
        head = newNode;
    }

    Worker pop() {
        if (!head) {
            std::cout << "Stack is empty.\n";
            return Worker();
        }
        Node* temp = head;
        Worker workerData = head->data;
        head = head->next;
        delete temp;
        return workerData;
    }

    bool isEmpty() const { return head == nullptr; }

    void show() const {
        Node* current = head;
        while (current) {
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

    Stack s;
    s.push(worker1);
    s.push(worker2);
    s.push(worker3);

    s.show();

    return 0;
}