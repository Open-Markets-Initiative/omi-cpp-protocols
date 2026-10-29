#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Code identifying this message type
enum class MessageType : char {
    SystemEventMessage = 'S',                                 // System Event Message
    TradeReportMessage = 'T',                                 // Trade Report Message
    LongFormTradeReportMessage = 't',                         // Long Form Trade Report Message
    NextSharesTradeReportMessage = 'M',                       // Next Shares Trade Report Message
    TradeCancelErrorMessage = 'X',                            // Trade Cancel Error Message
    LongFormTradeCancelErrorMessage = 'x',                    // Long Form Trade Cancel Error Message
    NextSharesTradeCancelErrorMessage = 'O',                  // Next Shares Trade Cancel Error Message
    TradeCorrectionMessage = 'C',                             // Trade Correction Message
    LongFormTradeCorrectionMessage = 'c',                     // Long Form Trade Correction Message
    NextSharesTradeCorrectionMessage = 'Z',                   // Next Shares Trade Correction Message
    StockTradingActionMessage = 'H',                          // Stock Trading Action Message
    StockDirectoryMessage = 'R',                              // Stock Directory Message
    RegShoShortSalePriceTestRestrictedIndicatorMessage = 'Y', // Reg Sho Short Sale Price Test Restricted Indicator Message
    AdjustedClosingPriceMessage = 'G',                        // Adjusted Closing Price Message
    LongFormAdjustedClosingPriceMessage = 'g',                // Long Form Adjusted Closing Price Message
    EndOfDayTradeSummaryMessage = 'J',                        // End Of Day Trade Summary Message
    LongFormEndOfDayTradeSummaryMessage = 'j',                // Long Form End Of Day Trade Summary Message
    NextSharesEndOfDayTradeSummaryMessage = 'N',              // Next Shares End Of Day Trade Summary Message
    IpoInformationMessage = 'I',                              // Ipo Information Message
    MwcbDeclineLevelMessage = 'V',                            // Mwcb Decline Level Message
    MwcbStatusMessage = 'W',                                  // Mwcb Status Message
    IpoQuotingPeriodUpdateMessage = 'K',                      // Ipo Quoting Period Update Message
    OperationalHaltMessage = 'h',                             // Operational Halt Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
