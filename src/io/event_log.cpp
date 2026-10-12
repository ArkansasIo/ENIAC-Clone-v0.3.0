#include "eniac/io/event_log.hpp"
#include <utility>
namespace eniac {
void EventLog::record(std::string message) { entries_.push_back(std::move(message)); }
const std::vector<std::string>& EventLog::entries() const noexcept { return entries_; }
void EventLog::clear() noexcept { entries_.clear(); }
} // namespace eniac
