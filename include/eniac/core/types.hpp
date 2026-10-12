#pragma once
#include <string_view>
namespace eniac {
enum class MachineState { Stopped, Running, Paused, Faulted };
[[nodiscard]] constexpr std::string_view to_string(MachineState state) noexcept {
    switch (state) {
    case MachineState::Stopped: return "Stopped";
    case MachineState::Running: return "Running";
    case MachineState::Paused: return "Paused";
    case MachineState::Faulted: return "Faulted";
    }
    return "Unknown";
}
} // namespace eniac
