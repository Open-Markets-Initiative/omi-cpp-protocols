#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Top of Strategy Market Quote Conditions
enum class BidCondition : char {
    Regular = 'A',                // Regular
    TradingHalt = 'T',            // Trading Halt
    Wide = 'W',                   // Wide
    SimpleAuction = 'S',          // Simple Auction
    ComplexAuction = 'C',         // Complex Auction
    SimpleMarketProtection = 'M', // Simple Market Protection
    LegMarketProtection = 'L',    // Leg Market Protection
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BidCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BidCondition value);

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
