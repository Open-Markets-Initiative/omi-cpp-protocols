#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Settlement related conditions.
enum class TradeCond1 : char {
    OutrightSeriesOrderquoteTradingElectronicallyWithAOutrightSeriesCubeOrderOrOutrightSeriesCubeOrderTradingElectronicallyWithOutrightSeriesCubeContraOrder = 'a', // Outright Series Orderquote Trading Electronically With A Outright Series Cube Order Or Outright Series Cube Order Trading Electronically With Outright Series Cube Contra Order
    TradingOfAnOutrightSeriesQccOrderOrCustomerToCustomerCrossOrder = 'c',                                                                                          // Trading Of An Outright Series Qcc Order Or Customer To Customer Cross Order
    OutrightSeriesFloorTrade = 'e',                                                                                                                                 // Outright Series Floor Trade
    AllOutrightSeriesElectronicTradesExcludingAwayMarketExecutionsThatWereNotPartOfCertainTransactions = 'I',                                                       // All Outright Series Electronic Trades Excluding Away Market Executions That Were Not Part Of Certain Transactions
    AllOutrightSeriesTradesGeneratedAsPartOfAnIntermarketSweepOrder = 'S',                                                                                          // All Outright Series Trades Generated As Part Of An Intermarket Sweep Order
    TransactionIsBeingReportedLateButIsInTheCorrectSequence = 'D',                                                                                                  // Transaction Is Being Reported Late But Is In The Correct Sequence
    ComplexOrderTradesThatWereNotPartOfCertainTransactions = 'f',                                                                                                   // Complex Order Trades That Were Not Part Of Certain Transactions
    ComplexOrderTradingElectronicallyWithAComplexCubeOrderOrComplexCubeOrderTradingElectronicallyWithComplexCubeContraOrder = 'g',                                  // Complex Order Trading Electronically With A Complex Cube Order Or Complex Cube Order Trading Electronically With Complex Cube Contra Order
    TradingOfAComplexQccOrderOrCustomerToCustomerCrossOrder = 'h',                                                                                                  // Trading Of A Complex Qcc Order Or Customer To Customer Cross Order
    ComplexOrderToComplexOrderFloorTrade = 'i',                                                                                                                     // Complex Order To Complex Order Floor Trade
    ComplexOrderTradingElectronicallyWithTheOutrightSeriesOrdersquotes = 'j',                                                                                       // Complex Order Trading Electronically With The Outright Series Ordersquotes
    ComplexOrderToOutrightSeriesOrderFloorTrade = 'm',                                                                                                              // Complex Order To Outright Series Order Floor Trade
    ComplexOrderWithStockToComplexOrderWithStockFloorTrade = 'p',                                                                                                   // Complex Order With Stock To Complex Order With Stock Floor Trade
    ComplexOrderWithStockToOutrightSeriesOrderFloorTrade = 's',                                                                                                     // Complex Order With Stock To Outright Series Order Floor Trade
    ExtendedHoursTrade = 'v',                                                                                                                                       // Extended Hours Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond1 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond1 value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
