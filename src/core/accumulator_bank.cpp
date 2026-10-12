#include "eniac/core/accumulator_bank.hpp"
namespace eniac {
Accumulator* AccumulatorBank::at(std::size_t index) noexcept { return index < count ? &accumulators_[index] : nullptr; }
const Accumulator* AccumulatorBank::at(std::size_t index) const noexcept { return index < count ? &accumulators_[index] : nullptr; }
void AccumulatorBank::clear() noexcept { for (auto& accumulator : accumulators_) accumulator.clear(); }
} // namespace eniac
