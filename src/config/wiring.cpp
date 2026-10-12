#include "eniac/config/wiring.hpp"
#include <utility>
namespace eniac {
bool Wiring::connect(std::string source, std::string destination) {
    if (source.empty() || destination.empty()) return false;
    routes_.push_back({std::move(source), std::move(destination)});
    return true;
}
const std::vector<WireRoute>& Wiring::routes() const noexcept { return routes_; }
} // namespace eniac
