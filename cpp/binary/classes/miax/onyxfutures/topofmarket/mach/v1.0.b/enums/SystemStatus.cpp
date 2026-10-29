#include "SystemStatus.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(SystemStatus value) {
    switch (value) {
        case SystemStatus::StartOfSystemHours: return "Start Of System Hours";
        case SystemStatus::EndOfSystemHours: return "End Of System Hours";
        case SystemStatus::StartOfTestSession: return "Start Of Test Session";
        case SystemStatus::EndOfTestSession: return "End Of Test Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SystemStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
