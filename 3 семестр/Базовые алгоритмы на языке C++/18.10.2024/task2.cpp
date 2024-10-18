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

    bool validate() const noexcept {
        float a = calculateSide(vertex1, vertex2);
        float b = calculateSide(vertex2, vertex3);
        float c = calculateSide(vertex3, vertex1);

        float maxSide = std::max(a, std::max(b, c));
        float othersSide = a + b + c - maxSide;

        if (maxSide >= othersSide) {
            std::cout << "Degenerate triangle\n";
            return false;
        }

        return true;
    }

    float calculateSquare(const Coords& c1, const Coords& c2, const Coords& c3) const noexcept {
        double a = calculateSide(c1, c2);
        double b = calculateSide(c2, c3);
        double c = calculateSide(c3, c1);
        double p = (a + b + c) / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    bool isInBounds(const Coords& point) const noexcept {
        float S = calculateSquare(vertex1, vertex2, vertex3); 
        float S1 = calculateSquare(point, vertex2, vertex3);
        float S2 = calculateSquare(vertex1, point, vertex3);
        float S3 = calculateSquare(vertex1, vertex2, point);

        return S == S1 + S2 + S3;
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
    if (!t.validate()) return 0;

    float x4, y4;
    std::cout << "x4 | y4: ";
    std::cin >> x4 >> y4;

    if (t.isInBounds(Coords(x4, y4))) std::cout << "in\n";
    else std::cout << "out\n";

    return 0;
}