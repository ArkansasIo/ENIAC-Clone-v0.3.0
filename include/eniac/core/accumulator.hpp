#pragma once

#include <cstdint>

namespace eniac {

struct AccumulatorFlags {
    bool overflow{false};
    bool negative{false};
};

class Accumulator {
public:
    Accumulator() = default;
    explicit Accumulator(long long value);

    [[nodiscard]] long long value() const noexcept;
    [[nodiscard]] const AccumulatorFlags& flags() const noexcept;
    void set(long long value) noexcept;
    void set_flags(AccumulatorFlags flags) noexcept;
    void clear() noexcept;

private:
    long long value_{0};
    AccumulatorFlags flags_{};
};

} // namespace eniac
