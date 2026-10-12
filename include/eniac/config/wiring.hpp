#pragma once

#include <string>
#include <vector>

namespace eniac {

struct WireRoute {
    std::string source;
    std::string destination;
};

class Wiring {
public:
    [[nodiscard]] bool connect(std::string source, std::string destination);
    [[nodiscard]] const std::vector<WireRoute>& routes() const noexcept;

private:
    std::vector<WireRoute> routes_;
};

} // namespace eniac
