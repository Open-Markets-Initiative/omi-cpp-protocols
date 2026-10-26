#include "EventCode.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(EventCode value) {
    switch (value) {
        case EventCode::BusinessTradeDateHasEnded: return "Business Trade Date Has Ended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
