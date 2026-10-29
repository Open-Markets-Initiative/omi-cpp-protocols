#include "SettlementType.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(SettlementType value) {
    switch (value) {
        case SettlementType::RegularSettlement: return "Regular Settlement";
        case SettlementType::CashTrade: return "Cash Trade";
        case SettlementType::NextDayTrade: return "Next Day Trade";
        case SettlementType::Seller: return "Seller";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SettlementType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
