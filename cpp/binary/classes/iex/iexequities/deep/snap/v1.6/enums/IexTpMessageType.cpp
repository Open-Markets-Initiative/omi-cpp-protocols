#include "IexTpMessageType.hpp"

namespace iex::iexequities::deep::snap::v1_6 {

std::string_view to_string(IexTpMessageType value) {
    switch (value) {
        case IexTpMessageType::SystemEventMessage: return "System Event Message";
        case IexTpMessageType::SecurityDirectoryMessage: return "Security Directory Message";
        case IexTpMessageType::TradingStatusMessage: return "Trading Status Message";
        case IexTpMessageType::RetailLiquidityIndicatorMessage: return "Retail Liquidity Indicator Message";
        case IexTpMessageType::OperationalHaltStatusMessage: return "Operational Halt Status Message";
        case IexTpMessageType::ShortSalePriceTestStatusMessage: return "Short Sale Price Test Status Message";
        case IexTpMessageType::SecurityEventMessage: return "Security Event Message";
        case IexTpMessageType::PriceLevelBuyUpdateMessage: return "Price Level Buy Update Message";
        case IexTpMessageType::PriceLevelSellUpdateMessage: return "Price Level Sell Update Message";
        case IexTpMessageType::TradeReportMessage: return "Trade Report Message";
        case IexTpMessageType::OfficialPriceMessage: return "Official Price Message";
        case IexTpMessageType::TradeBreakMessage: return "Trade Break Message";
        case IexTpMessageType::AuctionInformationMessage: return "Auction Information Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IexTpMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deep::snap::v1_6
