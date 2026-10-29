#include "CashMarginType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(CashMarginType value) {
    switch (value) {
        case CashMarginType::Cash: return "Cash";
        case CashMarginType::MarginOpenNegotiable: return "Margin Open Negotiable";
        case CashMarginType::MarginCloseNegotiable: return "Margin Close Negotiable";
        case CashMarginType::MarginOpenStandardized: return "Margin Open Standardized";
        case CashMarginType::MarginCloseStandardized: return "Margin Close Standardized";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CashMarginType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
