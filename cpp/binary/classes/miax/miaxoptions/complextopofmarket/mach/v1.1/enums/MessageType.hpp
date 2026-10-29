#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Code identifying this message type
enum class MessageType : char {
    SystemTimeMessage = '1',                           // System Time Message
    SeriesUpdate = 'P',                                // Series Update
    ComplexStrategyDefinitionMessage = 'C',            // Complex Strategy Definition Message
    SystemStateMessage = 'S',                          // System State Message
    CompactComplexTopOfMarketBidMessage = 'b',         // Compact Complex Top Of Market Bid Message
    CompactComplexTopOfMarketOfferMessage = 'o',       // Compact Complex Top Of Market Offer Message
    WideComplexTopOfMarketBidMessage = 'e',            // Wide Complex Top Of Market Bid Message
    WideComplexTopOfMarketOfferMessage = 'f',          // Wide Complex Top Of Market Offer Message
    CompactComplexDoubleSidedTopOfMarketMessage = 'm', // Compact Complex Double Sided Top Of Market Message
    WideComplexDoubleSidedTopOfMarketMessage = 'w',    // Wide Complex Double Sided Top Of Market Message
    StrategyTradeMessage = 't',                        // Strategy Trade Message
    UnderlyingTradingStatusMessage = 'H',              // Underlying Trading Status Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
