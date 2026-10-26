#include "OppositeSide.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(OppositeSide value) {
    switch (value) {
        case OppositeSide::Sell: return "Sell";
        case OppositeSide::Buy: return "Buy";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OppositeSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
