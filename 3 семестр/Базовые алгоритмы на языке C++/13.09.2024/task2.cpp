#include <iostream>
#include <cmath>

enum FunctionChoice {
    SQUARE_X,
    EXP,
    LN
};

class Solver {
private:
    FunctionChoice funcChoice;
    double a, b;
    int n; // кол-во разбиений

public:
    void setFunction(const FunctionChoice& choice) {
        this->funcChoice = choice;
    }

    void setLimits(const double& a, const double& b, const int& n) {
        this->a = a;
        this->b = b;
        this->n = n;
    }

    double calculateFunction(const double& x) {
        switch (funcChoice) {
            case SQUARE_X:
                return x * x;
            case EXP:
                return std::exp(x);
            case LN:
                return std::log(x);
            default:
                throw;
        }
    }

    double integrateRectangle() {
        double step = (b - a) / n;
        double result = 0.0;

        for (int i = 0; i < n; ++i) {
            double x = a + (i + 0.5) * step;
            result += calculateFunction(x);
        }

        return result * step;
    }

    double integrateTrapezoid() {
        double step = (b - a) / n;
        double result = 0.5 * (calculateFunction(a) + calculateFunction(b));

        for (int i = 1; i < n; ++i) {
            double x = a + i * step;
            result += calculateFunction(x);
        }

        return result * step;
    }

    double integrateSimpson() {
        if (n % 2 != 0) {
            std::cout << "Number should be even" << std::endl;
            return -1;
        }

        double step = (b - a) / n;
        double result = calculateFunction(a) + calculateFunction(b);

        for (int i = 1; i != n; ++i) {
            double x = a + i * step;
            result += calculateFunction(x) * (i % 2 == 0 ? 2 : 4);
        }

        return result * step / 3;
    }
};

int main() {
    Solver solver;

    solver.setFunction(LN);
    solver.setLimits(1, 7, 10e6);

    std::cout << "Integrated results...\n";
    std::cout << "Rectangle: " << solver.integrateRectangle() << std::endl;
    std::cout << "Simspon: " << solver.integrateSimpson() << std::endl;
    std::cout << "Trapezoid: " << solver.integrateTrapezoid() << std::endl;

    return 0;
}
