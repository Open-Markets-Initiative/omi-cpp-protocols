#include "MessageType.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::TradeReportMessage: return "Trade Report Message";
        case MessageType::LongFormTradeReportMessage: return "Long Form Trade Report Message";
        case MessageType::NextSharesTradeReportMessage: return "Next Shares Trade Report Message";
        case MessageType::TradeCancelErrorMessage: return "Trade Cancel Error Message";
        case MessageType::LongFormTradeCancelErrorMessage: return "Long Form Trade Cancel Error Message";
        case MessageType::NextSharesTradeCancelErrorMessage: return "Next Shares Trade Cancel Error Message";
        case MessageType::TradeCorrectionMessage: return "Trade Correction Message";
        case MessageType::LongFormTradeCorrectionMessage: return "Long Form Trade Correction Message";
        case MessageType::NextSharesTradeCorrectionMessage: return "Next Shares Trade Correction Message";
        case MessageType::StockTradingActionMessage: return "Stock Trading Action Message";
        case MessageType::StockDirectoryMessage: return "Stock Directory Message";
        case MessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: return "Reg Sho Short Sale Price Test Restricted Indicator Message";
        case MessageType::AdjustedClosingPriceMessage: return "Adjusted Closing Price Message";
        case MessageType::LongFormAdjustedClosingPriceMessage: return "Long Form Adjusted Closing Price Message";
        case MessageType::EndOfDayTradeSummaryMessage: return "End Of Day Trade Summary Message";
        case MessageType::LongFormEndOfDayTradeSummaryMessage: return "Long Form End Of Day Trade Summary Message";
        case MessageType::NextSharesEndOfDayTradeSummaryMessage: return "Next Shares End Of Day Trade Summary Message";
        case MessageType::IpoInformationMessage: return "Ipo Information Message";
        case MessageType::MwcbDeclineLevelMessage: return "Mwcb Decline Level Message";
        case MessageType::MwcbStatusMessage: return "Mwcb Status Message";
        case MessageType::IpoQuotingPeriodUpdateMessage: return "Ipo Quoting Period Update Message";
        case MessageType::OperationalHaltMessage: return "Operational Halt Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
