#include "TemplateId.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::string_view to_string(TemplateId value) {
    switch (value) {
        case TemplateId::InstrumentDirectoryMessage: return "Instrument Directory Message";
        case TemplateId::RegShoRestrictionMessage: return "Reg Sho Restriction Message";
        case TemplateId::SecurityTradingStatusMessage: return "Security Trading Status Message";
        case TemplateId::TradingSessionStatusMessage: return "Trading Session Status Message";
        case TemplateId::OrderAddedMessage: return "Order Added Message";
        case TemplateId::OrderDeletedMessage: return "Order Deleted Message";
        case TemplateId::OrderReducedMessage: return "Order Reduced Message";
        case TemplateId::OrderExecutedMessage: return "Order Executed Message";
        case TemplateId::TradeMessage: return "Trade Message";
        case TemplateId::BrokenTradeMessage: return "Broken Trade Message";
        case TemplateId::CorrectedTradeMessage: return "Corrected Trade Message";
        case TemplateId::ClearBookMessage: return "Clear Book Message";
        case TemplateId::SnapshotCompleteMessage: return "Snapshot Complete Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TemplateId value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
