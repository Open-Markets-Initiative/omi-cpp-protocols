#include "MessageType.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::SecurityDirectoryMessage: return "Security Directory Message";
        case MessageType::TradingStatusMessage: return "Trading Status Message";
        case MessageType::RetailLiquidityIndicatorMessage: return "Retail Liquidity Indicator Message";
        case MessageType::OperationalHaltStatusMessage: return "Operational Halt Status Message";
        case MessageType::ShortSalePriceTestStatusMessage: return "Short Sale Price Test Status Message";
        case MessageType::QuoteUpdateMessage: return "Quote Update Message";
        case MessageType::TradeReportMessage: return "Trade Report Message";
        case MessageType::OfficialPriceMessage: return "Official Price Message";
        case MessageType::TradeBreakMessage: return "Trade Break Message";
        case MessageType::AuctionInformationMessage: return "Auction Information Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::tops::iextp::v1_66
