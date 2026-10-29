#include "SystemEvent.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(SystemEvent value) {
    switch (value) {
        case SystemEvent::StartOfDay: return "Start Of Day";
        case SystemEvent::EndOfDay: return "End Of Day";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SystemEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
