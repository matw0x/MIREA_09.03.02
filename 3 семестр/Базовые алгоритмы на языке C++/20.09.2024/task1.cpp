#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

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
    const double analyticExpValue = std::exp(7) - std::exp(1);

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
            double x = a + i * step;
            result += calculateFunction(x);
        }

        return result * step;
    }

    double integrateTrapezoid() {
        double step = (b - a) / n;
        double result = 0.0;

        result += 0.5 * calculateFunction(a);
        result += 0.5 * calculateFunction(b);

        for (int i = 1; i < n; ++i) {
            double x = a + i * step;
            result += calculateFunction(x);
        }

        return result * step;
    }

    double integrateSimpson() {
        if (n % 2 != 0) {
            std::cout << "Number should be even" << std::endl;
            throw;
        }

        double step = (b - a) / n;
        double result = calculateFunction(a) + calculateFunction(b);

        for (int i = 1; i < n; ++i) {
            double x = a + i * step;
            result += (i % 2 == 0 ? 2 : 4) * calculateFunction(x);
        }

        return result * step / 3;
    }

    double calculateError(const double& numRes) const noexcept {
        return std::abs(numRes - analyticExpValue);
    }
};

int main() {
    Solver solver;
    const int a = 1; const int b = 7;

    solver.setFunction(EXP);

    const std::string filename = "result.csv";

    std::ofstream file(filename);
    file << "n,rectangle,trapeze,parabola\n";

    for (int n = 2; n <= 20; n += 2) {
        solver.setLimits(a, b, n);

        double rectIntegral = solver.integrateRectangle();
        double trapIntegral = solver.integrateTrapezoid();
        double simpIntegral = solver.integrateSimpson();

        double rectError = solver.calculateError(rectIntegral);
        double trapError = solver.calculateError(trapIntegral);
        double simpError = solver.calculateError(simpIntegral);

        const std::string result = std::to_string(n) + ',' + 
                                   std::to_string(rectError) + ',' + 
                                   std::to_string(trapError) + ',' + 
                                   std::to_string(simpError) + '\n';

        file << result;
    }

    file.close();

    return 0;
}