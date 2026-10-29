#include "OriginalSettlementType.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(OriginalSettlementType value) {
    switch (value) {
        case OriginalSettlementType::RegularSettlement: return "Regular Settlement";
        case OriginalSettlementType::CashSettlement: return "Cash Settlement";
        case OriginalSettlementType::NextDaySettlement: return "Next Day Settlement";
        case OriginalSettlementType::SellerSettlement: return "Seller Settlement";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OriginalSettlementType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
