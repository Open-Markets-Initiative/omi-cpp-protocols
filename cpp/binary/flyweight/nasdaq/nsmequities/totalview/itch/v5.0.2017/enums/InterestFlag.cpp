#include "InterestFlag.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

std::string_view to_string(InterestFlag value) {
    switch (value) {
        case InterestFlag::BuySideRpiOrdersAvailable: return "Buy Side Rpi Orders Available";
        case InterestFlag::SellSideRpiOrdersAvailable: return "Sell Side Rpi Orders Available";
        case InterestFlag::BothSidesRpiOrdersAvailable: return "Both Sides Rpi Orders Available";
        case InterestFlag::NoRpiOrdersAvailable: return "No Rpi Orders Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, InterestFlag value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
