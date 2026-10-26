#include "Side.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(Side value) {
    switch (value) {
        case Side::Sell: return "Sell";
        case Side::Buy: return "Buy";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Side value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
