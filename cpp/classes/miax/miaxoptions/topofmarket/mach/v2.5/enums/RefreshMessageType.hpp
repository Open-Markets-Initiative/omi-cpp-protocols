#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Identifies the data set the firm is requesting a refresh of.
enum class RefreshMessageType : char {
    SimpleSeriesUpdateRefresh = 'P',      // Simple Series Update Refresh
    SimpleTopOfMarketRefresh = 'Q',       // Simple Top Of Market Refresh
    UnderlyingTradingStatusRefresh = 'U', // Underlying Trading Status Refresh
    SystemStateRefresh = 'S',             // System State Refresh
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RefreshMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RefreshMessageType value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
