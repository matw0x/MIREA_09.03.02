// Реализовать три различных класса: triangle, rectangle и circle, каждый из
// которых имеет метод show, выводящий площадь соответствующей
// фигуры. Организовать очередь из трех различных фигур. Достать
// элементы из очереди и вывести их площади.

#include <iostream>
#include <cmath>
#include <queue>

class Figure {
public:
    virtual void show() const = 0;
    virtual ~Figure() = default;
};

class Triangle : public Figure {
private:
    double side1, side2, side3;

public:
    Triangle(const double& a, const double& b, const double& c) : side1(a), side2(b), side3(c) {}

    double area() const {
        double s = (side1 + side2 + side3) / 2;
        return std::sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    void show() const override { std::cout << "Triangle area: " << area() << std::endl; }
};

class Rectangle : public Figure {
private:
    double width, height;

public:
    Rectangle(const double& w, const double& h) : width(w), height(h) {}
    double area() const { return width * height; }
    void show() const override { std::cout << "Rectangle area: " << area() << std::endl; }
};

class Circle : public Figure {
private:
    double radius;

public:
    Circle(const double& r) : radius(r) {}
    double area() const { return M_PI * radius * radius; }
    void show() const override { std::cout << "Circle area: " << area() << std::endl; }
};

int main() {
    std::queue<Figure*> figures;
    figures.push(new Triangle(3, 4, 5));
    figures.push(new Rectangle(10, 4));
    figures.push(new Circle(2));

    while (!figures.empty()) {
        auto current = figures.front();
        current->show();
        delete current;
        figures.pop();
    }
    
    return 0;
}