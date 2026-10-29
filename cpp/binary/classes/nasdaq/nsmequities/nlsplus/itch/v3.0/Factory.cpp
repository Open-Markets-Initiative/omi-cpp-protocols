#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case TradeReportMessage::message_type: return std::make_unique<TradeReportMessage>();
        case LongFormTradeReportMessage::message_type: return std::make_unique<LongFormTradeReportMessage>();
        case NextSharesTradeReportMessage::message_type: return std::make_unique<NextSharesTradeReportMessage>();
        case TradeCancelErrorMessage::message_type: return std::make_unique<TradeCancelErrorMessage>();
        case LongFormTradeCancelErrorMessage::message_type: return std::make_unique<LongFormTradeCancelErrorMessage>();
        case NextSharesTradeCancelErrorMessage::message_type: return std::make_unique<NextSharesTradeCancelErrorMessage>();
        case TradeCorrectionMessage::message_type: return std::make_unique<TradeCorrectionMessage>();
        case LongFormTradeCorrectionMessage::message_type: return std::make_unique<LongFormTradeCorrectionMessage>();
        case NextSharesTradeCorrectionMessage::message_type: return std::make_unique<NextSharesTradeCorrectionMessage>();
        case StockTradingActionMessage::message_type: return std::make_unique<StockTradingActionMessage>();
        case StockDirectoryMessage::message_type: return std::make_unique<StockDirectoryMessage>();
        case RegShoShortSalePriceTestRestrictedIndicatorMessage::message_type: return std::make_unique<RegShoShortSalePriceTestRestrictedIndicatorMessage>();
        case AdjustedClosingPriceMessage::message_type: return std::make_unique<AdjustedClosingPriceMessage>();
        case LongFormAdjustedClosingPriceMessage::message_type: return std::make_unique<LongFormAdjustedClosingPriceMessage>();
        case EndOfDayTradeSummaryMessage::message_type: return std::make_unique<EndOfDayTradeSummaryMessage>();
        case LongFormEndOfDayTradeSummaryMessage::message_type: return std::make_unique<LongFormEndOfDayTradeSummaryMessage>();
        case NextSharesEndOfDayTradeSummaryMessage::message_type: return std::make_unique<NextSharesEndOfDayTradeSummaryMessage>();
        case IpoInformationMessage::message_type: return std::make_unique<IpoInformationMessage>();
        case MwcbDeclineLevelMessage::message_type: return std::make_unique<MwcbDeclineLevelMessage>();
        case MwcbStatusMessage::message_type: return std::make_unique<MwcbStatusMessage>();
        case IpoQuotingPeriodUpdateMessage::message_type: return std::make_unique<IpoQuotingPeriodUpdateMessage>();
        case OperationalHaltMessage::message_type: return std::make_unique<OperationalHaltMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
