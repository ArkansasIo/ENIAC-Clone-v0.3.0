#pragma once

namespace eniac {

struct ArithmeticResult {
    long long value{};
    bool overflow{};
};

class DecimalALU {
public:
    [[nodiscard]] ArithmeticResult add(long long left, long long right) const;
    [[nodiscard]] ArithmeticResult subtract(long long left, long long right) const;
    [[nodiscard]] ArithmeticResult multiply(long long left, long long right) const;
};

} // namespace eniac
