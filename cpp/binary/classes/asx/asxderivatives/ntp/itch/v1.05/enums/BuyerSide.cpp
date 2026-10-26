#include "BuyerSide.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(BuyerSide value) {
    switch (value) {
        case BuyerSide::Sell: return "Sell";
        case BuyerSide::Buy: return "Buy";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BuyerSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
