#pragma once
#include <array>
#include <cstddef>
#include "eniac/core/accumulator.hpp"
namespace eniac {
class AccumulatorBank {
public:
    static constexpr std::size_t count = 20;
    [[nodiscard]] Accumulator* at(std::size_t index) noexcept;
    [[nodiscard]] const Accumulator* at(std::size_t index) const noexcept;
    void clear() noexcept;
private:
    std::array<Accumulator, count> accumulators_{};
};
} // namespace eniac
