#include "MessageType.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::StockDirectoryMessage: return "Stock Directory Message";
        case MessageType::StockTradingActionMessage: return "Stock Trading Action Message";
        case MessageType::RegShoRestrictionMessage: return "Reg Sho Restriction Message";
        case MessageType::MwcbDeclineLevelMessage: return "Mwcb Decline Level Message";
        case MessageType::MwcbBreachMessage: return "Mwcb Breach Message";
        case MessageType::OperationalHaltMessage: return "Operational Halt Message";
        case MessageType::BboQuotationMessage: return "Bbo Quotation Message";
        case MessageType::PriceImprovementMessage: return "Price Improvement Message";
        case MessageType::IpoQuotingPeriodUpdateMessage: return "Ipo Quoting Period Update Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
