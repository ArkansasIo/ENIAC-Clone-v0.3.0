#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>
namespace cpm22 {
class Memory {
public:
 static constexpr std::size_t capacity=65536;
 Memory()=default;
 [[nodiscard]] std::optional<std::uint8_t> read(std::size_t a) const noexcept;
 bool write(std::size_t a,std::uint8_t v) noexcept;
 bool fill(std::size_t a,std::size_t n,std::uint8_t v) noexcept;
 [[nodiscard]] std::optional<std::vector<std::uint8_t>> snapshot(std::size_t a,std::size_t n) const;
 bool restore(std::size_t a,const std::vector<std::uint8_t>& bytes) noexcept;
 void clear(std::uint8_t v=0) noexcept;
private: std::array<std::uint8_t,capacity> bytes_{};
};
}
