#include "ShortSellingState.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

std::string_view to_string(ShortSellingState value) {
    switch (value) {
        case ShortSellingState::NoPriceRestriction: return "No Price Restriction";
        case ShortSellingState::PriceRestrictionInEffect: return "Price Restriction In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ShortSellingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::itch::v1_6
