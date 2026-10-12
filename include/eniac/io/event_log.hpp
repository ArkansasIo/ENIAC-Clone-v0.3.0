#pragma once
#include <string>
#include <vector>
namespace eniac {
class EventLog {
public:
    void record(std::string message);
    [[nodiscard]] const std::vector<std::string>& entries() const noexcept;
    void clear() noexcept;
private:
    std::vector<std::string> entries_;
};
} // namespace eniac
