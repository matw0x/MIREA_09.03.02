// Реализовать класс Point2D с координатами точек x и y. Перегрузить
// операцию сложения так, чтобы при сложении двух точек получалась
// третья, координаты которой равны сумме соответствующих координат.
// Перегрузить вывод << через cout таким образом, чтобы можно было
// выводить точки в формате (x;y).

#include <iostream>
#include <ostream>

class Point2D {
private:
    double x, y;

public:
    Point2D(const double& x = 0, const double& y = 0) : x(x), y(y) {}
    Point2D operator+(const Point2D& other) const { return Point2D(x + other.x, y + other.y); }

    friend std::ostream& operator<<(std::ostream& os, const Point2D& point) {
        os << '(' << point.x << ';' << point.y << ')';
        return os;
    }
};

int main() {
    Point2D p1(-2.8, 3.333);
    Point2D p2(4.0, 5.0);

    Point2D p3 = p1 + p2;

    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3 (p1 + p2): " << p3 << std::endl;

    return 0;
}