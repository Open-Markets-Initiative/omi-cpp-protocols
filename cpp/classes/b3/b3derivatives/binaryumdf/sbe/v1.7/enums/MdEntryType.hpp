#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// mDEntryType
enum class MdEntryType : char {
    Bid = '0',                       // Bid
    Offer = '1',                     // Offer
    Trade = '2',                     // Trade
    IndexValue = '3',                // Index Value
    OpeningPrice = '4',              // Opening Price
    ClosingPrice = '5',              // Closing Price
    SettlementPrice = '6',           // Settlement Price
    SessionHighPrice = '7',          // Session High Price
    SessionLowPrice = '8',           // Session Low Price
    ExecutionStatistics = '9',       // Execution Statistics
    Imbalance = 'A',                 // Imbalance
    TradeVolume = 'B',               // Trade Volume
    OpenInterest = 'C',              // Open Interest
    EmptyBook = 'J',                 // Empty Book
    SecurityTradingStatePhase = 'c', // Security Trading State Phase
    PriceBand = 'g',                 // Price Band
    QuantityBand = 'h',              // Quantity Band
    CompositeUnderlyingPrice = 'D',  // Composite Underlying Price
    ExecutionSummary = 's',          // Execution Summary
    VolatilityPrice = 'v',           // Volatility Price
    TradeBust = 'u',                 // Trade Bust
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdEntryType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdEntryType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
