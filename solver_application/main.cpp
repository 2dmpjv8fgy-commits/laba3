#include <iostream>
#include "formatter.h"
#include "solver.h"

int main() {
    float a = 1, b = -3, c = 2;
    float x1, x2;
    try {
        solve(a, b, c, x1, x2);
        std::string result = "x1 = " + std::to_string(x1) + ", x2 = " + std::to_string(x2);
        std::cout << formatter(result) << std::endl;
    } catch (const std::exception& e) {
        std::cout << formatter(e.what()) << std::endl;
    }
    return 0;
}
