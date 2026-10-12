#include <iostream>

#include "eniac/arithmetic/decimal_alu.hpp"

int main() {
    eniac::DecimalALU alu;
    long long total = 0;
    for (long long value = 1; value <= 10; ++value) {
        total = alu.add(total, value).value;
    }
    std::cout << "sum(1..10) = " << total << '\n';
}
