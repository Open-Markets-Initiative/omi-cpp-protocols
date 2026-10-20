#include "SystemEvent.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

std::string_view to_string(SystemEvent value) {
    switch (value) {
        case SystemEvent::StartOfMessages: return "Start Of Messages";
        case SystemEvent::StartOfSystemHours: return "Start Of System Hours";
        case SystemEvent::StartOfRegularMarketHours: return "Start Of Regular Market Hours";
        case SystemEvent::EndOfRegularMarketHours: return "End Of Regular Market Hours";
        case SystemEvent::EndOfSystemHours: return "End Of System Hours";
        case SystemEvent::EndOfMessages: return "End Of Messages";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SystemEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deep::snap::v1_6
