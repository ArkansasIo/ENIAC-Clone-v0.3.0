#pragma once
#include <cstdint>
namespace eniac {
class MachineClock {
public:
    void tick() noexcept;
    void reset() noexcept;
    [[nodiscard]] std::uint64_t cycles() const noexcept;
private:
    std::uint64_t cycles_{0};
};
} // namespace eniac
