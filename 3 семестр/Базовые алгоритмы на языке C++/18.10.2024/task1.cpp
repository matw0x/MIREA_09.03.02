#include <iostream>
#include <cmath>

struct Coords {
    float x, y;

    Coords(const float& x, const float& y) noexcept :
    x(x), y(y) {}
};

struct Triangle {
    Coords vertex1, vertex2, vertex3;

    Triangle(const Coords& c1, const Coords& c2, const Coords& c3) noexcept : 
    vertex1(c1), vertex2(c2), vertex3(c3) {}

    double calculateSide(const Coords& a, const Coords& b) const noexcept {
        return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
    }

    void showTriangleType() const noexcept {
        float a = calculateSide(vertex1, vertex2);
        float b = calculateSide(vertex2, vertex3);
        float c = calculateSide(vertex3, vertex1);

        float maxSide = std::max(a, std::max(b, c));
        float othersSide = a + b + c - maxSide;

        if (maxSide >= othersSide) {
            std::cout << "Degenerate triangle\n";
            return;
        }

        float cosA = (b*b + c*c - a*a) / (2*b*c);
        float cosB = (a*a + c*c - b*b) / (2*a*c);
        float cosC = (a*a + b*b - c*c) / (2*a*b);

        if (cosA == 0 || cosB == 0 || cosC == 0) {
            std::cout << "Right triangle\n";
        } else if (cosA > 0 && cosB > 0 && cosC > 0) {
            std::cout << "Acute triangle\n";
        } else {
            std::cout << "Obtuse triangle\n";
        }
    }
};


int main() {
    float x1, y1;
    float x2, y2;
    float x3, y3;

    std::cout << "x1 | y1: ";
    std::cin >> x1 >> y1;
    std::cout << "x2 | y2: ";
    std::cin >> x2 >> y2;
    std::cout << "x3 | y3: ";
    std::cin >> x3 >> y3;

    Triangle t(Coords(x1, y1), Coords(x2, y2), Coords(x3, y3));
    t.showTriangleType();

    return 0;
}