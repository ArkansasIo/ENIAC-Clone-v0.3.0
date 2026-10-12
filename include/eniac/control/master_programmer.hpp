#pragma once

#include <cstddef>

namespace eniac {

class MasterProgrammer {
public:
    explicit MasterProgrammer(std::size_t repetitions = 1);
    [[nodiscard]] bool has_next() const noexcept;
    void advance() noexcept;
    void reset() noexcept;
    [[nodiscard]] std::size_t current_iteration() const noexcept;

private:
    std::size_t repetitions_{1};
    std::size_t current_{0};
};

} // namespace eniac
