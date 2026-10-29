#include "CorrectedSettlementType.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(CorrectedSettlementType value) {
    switch (value) {
        case CorrectedSettlementType::RegularSettlement: return "Regular Settlement";
        case CorrectedSettlementType::CashSettlement: return "Cash Settlement";
        case CorrectedSettlementType::NextDaySettlement: return "Next Day Settlement";
        case CorrectedSettlementType::SellerSettlement: return "Seller Settlement";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CorrectedSettlementType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
