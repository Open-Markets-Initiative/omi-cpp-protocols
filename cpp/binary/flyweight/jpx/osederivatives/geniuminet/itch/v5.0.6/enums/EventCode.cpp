#include "EventCode.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::string_view to_string(EventCode value) {
    switch (value) {
        case EventCode::StartOfMessages: return "Start Of Messages";
        case EventCode::EndOfMessages: return "End Of Messages";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
