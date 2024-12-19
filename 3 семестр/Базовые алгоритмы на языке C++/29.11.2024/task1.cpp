// Очередь – это последовательность элементов, над которыми
// разрешены только две операции: добавить новый элемент в конец
// очереди и убрать головной элемент из последовательности.
// Реализовать очередь из элементов класса Worker на основе
// динамического массива. Поместить в очередь трех воркеров, достать
// их из очереди и вывести на экран.

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
    Worker* array;
    size_t capacity, size;

public:
    Queue(const size_t& initialCapacity) : capacity(initialCapacity), size(0) {
        array = new Worker[capacity];
    }

    ~Queue() { delete[] array; }

    void push(const Worker& value) {
        if (size == capacity) {
            resize(capacity * 2);
        }

        array[size++] = value;
    }

    void pop() {
        if (isEmpty()) throw std::out_of_range("Queue is empty!\n");

        for (size_t i = 1; i < size; ++i) array[i - 1] = array[i];

        --size;
    }

    bool isEmpty() const { return size == 0; }

    void show() const {
        for (size_t i = 0; i != size; ++i) array[i].print();
    }

private:
    void resize(const size_t& newCapacity) {
        Worker* newArray = new Worker[newCapacity];

        for (size_t i = 0; i != size; ++i) newArray[i] = std::move(array[i]);

        delete[] array;
        array = newArray;
        capacity = newCapacity;
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

    Queue q(3);
    q.push(worker1);
    q.push(worker2);
    q.push(worker3);

    q.show();

    return 0;
}