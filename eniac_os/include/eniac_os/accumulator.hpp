#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace eniac_os {
inline constexpr std::size_t accumulator_count = 20;

class AccumulatorBank {
public:
    void reset() noexcept;
    [[nodiscard]] bool valid_index(std::size_t index) const noexcept;
    [[nodiscard]] std::int64_t get(std::size_t index) const;
    void set(std::size_t index, std::int64_t value);
    void add(std::size_t index, std::int64_t value);
    void subtract(std::size_t index, std::int64_t value);
    void multiply(std::size_t index, std::int64_t value);
    void divide(std::size_t index, std::int64_t value);
    [[nodiscard]] std::string describe() const;
private:
    std::array<std::int64_t, accumulator_count> values_{};
};
} // namespace eniac_os
