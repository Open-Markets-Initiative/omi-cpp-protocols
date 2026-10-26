#include "TradeCondition.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::Regular: return "Regular";
        case TradeCondition::CancelOfTradePreviouslyReportedOtherThanAsTheLastOrOpening: return "Cancel Of Trade Previously Reported Other Than As The Last Or Opening";
        case TradeCondition::LateAndIsOutOfSequence: return "Late And Is Out Of Sequence";
        case TradeCondition::CancelOfTheLastReportedTrade: return "Cancel Of The Last Reported Trade";
        case TradeCondition::LateAndIsInCorrectSequence: return "Late And Is In Correct Sequence";
        case TradeCondition::CancelOfTheFirstReportedTrade: return "Cancel Of The First Reported Trade";
        case TradeCondition::LateReportOfTheOpeningTradeAndIsOutOfSequence: return "Late Report Of The Opening Trade And Is Out Of Sequence";
        case TradeCondition::CancelOfTheOnlyReportedTrade: return "Cancel Of The Only Reported Trade";
        case TradeCondition::LateReportOfTheOpeningTradeAndIsInCorrectSequence: return "Late Report Of The Opening Trade And Is In Correct Sequence";
        case TradeCondition::Auto: return "Auto";
        case TradeCondition::ReopeningOfAnOption: return "Reopening Of An Option";
        case TradeCondition::Reserved: return "Reserved";
        case TradeCondition::ABuyAndASellInTheSameClass: return "A Buy And A Sell In The Same Class";
        case TradeCondition::ABuyAndASellInAPutAndACall: return "A Buy And A Sell In A Put And A Call";
        case TradeCondition::Reserved2: return "Reserved";
        case TradeCondition::Reserved3: return "Reserved";
        case TradeCondition::BuyOrSellOfACallOrPut: return "Buy Or Sell Of A Call Or Put";
        case TradeCondition::BuyOfACallAndASellOfAPutForTheSameUnderlyingStockOrIndex: return "Buy Of A Call And A Sell Of A Put For The Same Underlying Stock Or Index";
        case TradeCondition::ExecutionOfAnOrderWhichWasStoppedAtAPriceThatDidNotConstituteATradeThroughOnAnotherMarketAtTheTimeOfTheStop: return "Execution Of An Order Which Was Stopped At A Price That Did Not Constitute A Trade Through On Another Market At The Time Of The Stop";
        case TradeCondition::ExecutionOfAnIsoOrder: return "Execution Of An Iso Order";
        case TradeCondition::Reserved4: return "Reserved";
        case TradeCondition::TradeThroughExempt: return "Trade Through Exempt";
        case TradeCondition::PairedPrime: return "Paired Prime";
        case TradeCondition::IsoPairedPrime: return "Iso Paired Prime";
        case TradeCondition::PrimeCustomerToCustomerCrossOrPrimeQcc: return "Prime Customer To Customer Cross Or Prime Qcc";
        case TradeCondition::Reserved5: return "Reserved";
        case TradeCondition::Reserved6: return "Reserved";
        case TradeCondition::ComplexTransactionThatIsNotComplexStockTiedAndDoesNotInvolveLegging: return "Complex Transaction That Is Not Complex Stock Tied And Does Not Involve Legging";
        case TradeCondition::ComplexPrimeTransactionThatIsNotComplexStockTiedAndDoesNotInvolveLegging: return "Complex Prime Transaction That Is Not Complex Stock Tied And Does Not Involve Legging";
        case TradeCondition::ComplexPrimeCustomerToCustomerCrossOrComplexPrimeQccTransactionThatIsNotComplexStockTied: return "Complex Prime Customer To Customer Cross Or Complex Prime Qcc Transaction That Is Not Complex Stock Tied";
        case TradeCondition::Reserved7: return "Reserved";
        case TradeCondition::ComplexLeggingTransactionThatIsNotComplexStockTied: return "Complex Legging Transaction That Is Not Complex Stock Tied";
        case TradeCondition::ComplexPrimeStockTiedTransactionThatDoesNotInvolveLegging: return "Complex Prime Stock Tied Transaction That Does Not Involve Legging";
        case TradeCondition::ComplexPrimeLeggingTransactionThatIsNotComplexStockTied: return "Complex Prime Legging Transaction That Is Not Complex Stock Tied";
        case TradeCondition::Reserved8: return "Reserved";
        case TradeCondition::ComplexStockTiedTransactionThatDoesNotInvolveLegging: return "Complex Stock Tied Transaction That Does Not Involve Legging";
        case TradeCondition::ComplexCustomerToCustomerCrossStockTiedOrComplexQccStockTiedTransaction: return "Complex Customer To Customer Cross Stock Tied Or Complex Qcc Stock Tied Transaction";
        case TradeCondition::Reserved9: return "Reserved";
        case TradeCondition::Reserved10: return "Reserved";
        case TradeCondition::Reserved11: return "Reserved";
        case TradeCondition::Reserved12: return "Reserved";
        case TradeCondition::Reserved13: return "Reserved";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
