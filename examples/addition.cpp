#include <iostream>

#include "eniac/arithmetic/decimal_alu.hpp"

int main() {
    eniac::DecimalALU alu;
    const auto result = alu.add(125, 375);
    std::cout << "125 + 375 = " << result.value << '\n';
}
