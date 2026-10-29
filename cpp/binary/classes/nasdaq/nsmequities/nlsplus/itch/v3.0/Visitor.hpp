#pragma once

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

class SystemEventMessage;
class TradeReportMessage;
class LongFormTradeReportMessage;
class NextSharesTradeReportMessage;
class TradeCancelErrorMessage;
class LongFormTradeCancelErrorMessage;
class NextSharesTradeCancelErrorMessage;
class TradeCorrectionMessage;
class LongFormTradeCorrectionMessage;
class NextSharesTradeCorrectionMessage;
class StockTradingActionMessage;
class StockDirectoryMessage;
class RegShoShortSalePriceTestRestrictedIndicatorMessage;
class AdjustedClosingPriceMessage;
class LongFormAdjustedClosingPriceMessage;
class EndOfDayTradeSummaryMessage;
class LongFormEndOfDayTradeSummaryMessage;
class NextSharesEndOfDayTradeSummaryMessage;
class IpoInformationMessage;
class MwcbDeclineLevelMessage;
class MwcbStatusMessage;
class IpoQuotingPeriodUpdateMessage;
class OperationalHaltMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const TradeReportMessage&) {}
    virtual void visit(const LongFormTradeReportMessage&) {}
    virtual void visit(const NextSharesTradeReportMessage&) {}
    virtual void visit(const TradeCancelErrorMessage&) {}
    virtual void visit(const LongFormTradeCancelErrorMessage&) {}
    virtual void visit(const NextSharesTradeCancelErrorMessage&) {}
    virtual void visit(const TradeCorrectionMessage&) {}
    virtual void visit(const LongFormTradeCorrectionMessage&) {}
    virtual void visit(const NextSharesTradeCorrectionMessage&) {}
    virtual void visit(const StockTradingActionMessage&) {}
    virtual void visit(const StockDirectoryMessage&) {}
    virtual void visit(const RegShoShortSalePriceTestRestrictedIndicatorMessage&) {}
    virtual void visit(const AdjustedClosingPriceMessage&) {}
    virtual void visit(const LongFormAdjustedClosingPriceMessage&) {}
    virtual void visit(const EndOfDayTradeSummaryMessage&) {}
    virtual void visit(const LongFormEndOfDayTradeSummaryMessage&) {}
    virtual void visit(const NextSharesEndOfDayTradeSummaryMessage&) {}
    virtual void visit(const IpoInformationMessage&) {}
    virtual void visit(const MwcbDeclineLevelMessage&) {}
    virtual void visit(const MwcbStatusMessage&) {}
    virtual void visit(const IpoQuotingPeriodUpdateMessage&) {}
    virtual void visit(const OperationalHaltMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
