#pragma once

#include <vector>

namespace eniac {

enum class OperationCode { Add, Subtract, Multiply, LoadConstant };

struct Operation {
    OperationCode code{};
    int destination{};
    int source{};
    long long constant{};
};

class Program {
public:
    void append(Operation operation);
    [[nodiscard]] const std::vector<Operation>& operations() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

private:
    std::vector<Operation> operations_;
};

} // namespace eniac
