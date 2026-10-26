#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Trade Condition Values. Please refer to Appendix A.
enum class TradeCondition : char {
    Regular = ' ',                                                                                                     // Regular
    CancelOfTradePreviouslyReportedOtherThanAsTheLastOrOpening = 'A',                                                  // Cancel Of Trade Previously Reported Other Than As The Last Or Opening
    LateAndIsOutOfSequence = 'B',                                                                                      // Late And Is Out Of Sequence
    CancelOfTheLastReportedTrade = 'C',                                                                                // Cancel Of The Last Reported Trade
    LateAndIsInCorrectSequence = 'D',                                                                                  // Late And Is In Correct Sequence
    CancelOfTheFirstReportedTrade = 'E',                                                                               // Cancel Of The First Reported Trade
    LateReportOfTheOpeningTradeAndIsOutOfSequence = 'F',                                                               // Late Report Of The Opening Trade And Is Out Of Sequence
    CancelOfTheOnlyReportedTrade = 'G',                                                                                // Cancel Of The Only Reported Trade
    LateReportOfTheOpeningTradeAndIsInCorrectSequence = 'H',                                                           // Late Report Of The Opening Trade And Is In Correct Sequence
    Auto = 'I',                                                                                                        // Auto
    ReopeningOfAnOption = 'J',                                                                                         // Reopening Of An Option
    Reserved = 'K',                                                                                                    // Reserved
    ABuyAndASellInTheSameClass = 'L',                                                                                  // A Buy And A Sell In The Same Class
    ABuyAndASellInAPutAndACall = 'M',                                                                                  // A Buy And A Sell In A Put And A Call
    Reserved2 = 'N',                                                                                                   // Reserved
    Reserved3 = 'O',                                                                                                   // Reserved
    BuyOrSellOfACallOrPut = 'P',                                                                                       // Buy Or Sell Of A Call Or Put
    BuyOfACallAndASellOfAPutForTheSameUnderlyingStockOrIndex = 'Q',                                                    // Buy Of A Call And A Sell Of A Put For The Same Underlying Stock Or Index
    ExecutionOfAnOrderWhichWasStoppedAtAPriceThatDidNotConstituteATradeThroughOnAnotherMarketAtTheTimeOfTheStop = 'R', // Execution Of An Order Which Was Stopped At A Price That Did Not Constitute A Trade Through On Another Market At The Time Of The Stop
    ExecutionOfAnIsoOrder = 'S',                                                                                       // Execution Of An Iso Order
    Reserved4 = 'T',                                                                                                   // Reserved
    TradeThroughExempt = 'X',                                                                                          // Trade Through Exempt
    PairedPrime = 'a',                                                                                                 // Paired Prime
    IsoPairedPrime = 'b',                                                                                              // Iso Paired Prime
    PrimeCustomerToCustomerCrossOrPrimeQcc = 'c',                                                                      // Prime Customer To Customer Cross Or Prime Qcc
    Reserved5 = 'd',                                                                                                   // Reserved
    Reserved6 = 'e',                                                                                                   // Reserved
    ComplexTransactionThatIsNotComplexStockTiedAndDoesNotInvolveLegging = 'f',                                         // Complex Transaction That Is Not Complex Stock Tied And Does Not Involve Legging
    ComplexPrimeTransactionThatIsNotComplexStockTiedAndDoesNotInvolveLegging = 'g',                                    // Complex Prime Transaction That Is Not Complex Stock Tied And Does Not Involve Legging
    ComplexPrimeCustomerToCustomerCrossOrComplexPrimeQccTransactionThatIsNotComplexStockTied = 'h',                    // Complex Prime Customer To Customer Cross Or Complex Prime Qcc Transaction That Is Not Complex Stock Tied
    Reserved7 = 'i',                                                                                                   // Reserved
    ComplexLeggingTransactionThatIsNotComplexStockTied = 'j',                                                          // Complex Legging Transaction That Is Not Complex Stock Tied
    ComplexPrimeStockTiedTransactionThatDoesNotInvolveLegging = 'k',                                                   // Complex Prime Stock Tied Transaction That Does Not Involve Legging
    ComplexPrimeLeggingTransactionThatIsNotComplexStockTied = 'l',                                                     // Complex Prime Legging Transaction That Is Not Complex Stock Tied
    Reserved8 = 'm',                                                                                                   // Reserved
    ComplexStockTiedTransactionThatDoesNotInvolveLegging = 'n',                                                        // Complex Stock Tied Transaction That Does Not Involve Legging
    ComplexCustomerToCustomerCrossStockTiedOrComplexQccStockTiedTransaction = 'o',                                     // Complex Customer To Customer Cross Stock Tied Or Complex Qcc Stock Tied Transaction
    Reserved9 = 'p',                                                                                                   // Reserved
    Reserved10 = 'q',                                                                                                  // Reserved
    Reserved11 = 'r',                                                                                                  // Reserved
    Reserved12 = 's',                                                                                                  // Reserved
    Reserved13 = 't',                                                                                                  // Reserved
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
