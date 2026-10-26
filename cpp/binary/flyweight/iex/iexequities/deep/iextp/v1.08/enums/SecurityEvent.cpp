#include "SecurityEvent.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

std::string_view to_string(SecurityEvent value) {
    switch (value) {
        case SecurityEvent::OpeningProcessComplete: return "Opening Process Complete";
        case SecurityEvent::ClosingProcessComplete: return "Closing Process Complete";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deep::iextp::v1_08
