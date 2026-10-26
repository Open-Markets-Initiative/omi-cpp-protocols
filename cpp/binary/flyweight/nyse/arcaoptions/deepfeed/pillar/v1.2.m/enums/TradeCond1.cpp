#include "TradeCond1.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(TradeCond1 value) {
    switch (value) {
        case TradeCond1::OutrightSeriesOrderquoteTradingElectronicallyWithAOutrightSeriesCubeOrderOrOutrightSeriesCubeOrderTradingElectronicallyWithOutrightSeriesCubeContraOrder: return "Outright Series Orderquote Trading Electronically With A Outright Series Cube Order Or Outright Series Cube Order Trading Electronically With Outright Series Cube Contra Order";
        case TradeCond1::TradingOfAnOutrightSeriesQccOrderOrCustomerToCustomerCrossOrder: return "Trading Of An Outright Series Qcc Order Or Customer To Customer Cross Order";
        case TradeCond1::OutrightSeriesFloorTrade: return "Outright Series Floor Trade";
        case TradeCond1::AllOutrightSeriesElectronicTradesExcludingAwayMarketExecutionsThatWereNotPartOfCertainTransactions: return "All Outright Series Electronic Trades Excluding Away Market Executions That Were Not Part Of Certain Transactions";
        case TradeCond1::AllOutrightSeriesTradesGeneratedAsPartOfAnIntermarketSweepOrder: return "All Outright Series Trades Generated As Part Of An Intermarket Sweep Order";
        case TradeCond1::TransactionIsBeingReportedLateButIsInTheCorrectSequence: return "Transaction Is Being Reported Late But Is In The Correct Sequence";
        case TradeCond1::ComplexOrderTradesThatWereNotPartOfCertainTransactions: return "Complex Order Trades That Were Not Part Of Certain Transactions";
        case TradeCond1::ComplexOrderTradingElectronicallyWithAComplexCubeOrderOrComplexCubeOrderTradingElectronicallyWithComplexCubeContraOrder: return "Complex Order Trading Electronically With A Complex Cube Order Or Complex Cube Order Trading Electronically With Complex Cube Contra Order";
        case TradeCond1::TradingOfAComplexQccOrderOrCustomerToCustomerCrossOrder: return "Trading Of A Complex Qcc Order Or Customer To Customer Cross Order";
        case TradeCond1::ComplexOrderToComplexOrderFloorTrade: return "Complex Order To Complex Order Floor Trade";
        case TradeCond1::ComplexOrderTradingElectronicallyWithTheOutrightSeriesOrdersquotes: return "Complex Order Trading Electronically With The Outright Series Ordersquotes";
        case TradeCond1::ComplexOrderToOutrightSeriesOrderFloorTrade: return "Complex Order To Outright Series Order Floor Trade";
        case TradeCond1::ComplexOrderWithStockToComplexOrderWithStockFloorTrade: return "Complex Order With Stock To Complex Order With Stock Floor Trade";
        case TradeCond1::ComplexOrderWithStockToOutrightSeriesOrderFloorTrade: return "Complex Order With Stock To Outright Series Order Floor Trade";
        case TradeCond1::ExtendedHoursTrade: return "Extended Hours Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCond1 value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
