#include "SellerSide.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(SellerSide value) {
    switch (value) {
        case SellerSide::Sell: return "Sell";
        case SellerSide::Buy: return "Buy";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SellerSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
