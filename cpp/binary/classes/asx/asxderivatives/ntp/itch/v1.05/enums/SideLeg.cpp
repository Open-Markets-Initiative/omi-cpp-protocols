#include "SideLeg.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(SideLeg value) {
    switch (value) {
        case SideLeg::Buy: return "Buy";
        case SideLeg::Sell: return "Sell";
        case SideLeg::NotDefined: return "Not Defined";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SideLeg value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
