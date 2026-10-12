#include "cpm22/memory.hpp"
#include <algorithm>
namespace cpm22 {
std::optional<std::uint8_t> Memory::read(std::size_t a) const noexcept { if(a>=capacity)return {}; return bytes_[a]; }
bool Memory::write(std::size_t a,std::uint8_t v) noexcept { if(a>=capacity)return false; bytes_[a]=v; return true; }
bool Memory::fill(std::size_t a,std::size_t n,std::uint8_t v) noexcept { if(a>capacity||n>capacity-a)return false; std::fill(bytes_.begin()+static_cast<std::ptrdiff_t>(a),bytes_.begin()+static_cast<std::ptrdiff_t>(a+n),v); return true; }
std::optional<std::vector<std::uint8_t>> Memory::snapshot(std::size_t a,std::size_t n) const { if(a>capacity||n>capacity-a)return {}; return std::vector<std::uint8_t>(bytes_.begin()+static_cast<std::ptrdiff_t>(a),bytes_.begin()+static_cast<std::ptrdiff_t>(a+n)); }
bool Memory::restore(std::size_t a,const std::vector<std::uint8_t>& b) noexcept { if(a>capacity||b.size()>capacity-a)return false; std::copy(b.begin(),b.end(),bytes_.begin()+static_cast<std::ptrdiff_t>(a)); return true; }
void Memory::clear(std::uint8_t v) noexcept { bytes_.fill(v); }
}
