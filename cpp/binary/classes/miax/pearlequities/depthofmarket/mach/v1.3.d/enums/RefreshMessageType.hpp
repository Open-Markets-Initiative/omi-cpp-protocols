#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Identifies the data set the firm is requesting a refresh of.
enum class RefreshMessageType : char {
    SymbolUpdateRefresh = 'S',          // Symbol Update Refresh
    SecurityTradingStatusRefresh = 't', // Security Trading Status Refresh
    SystemStateRefresh = 's',           // System State Refresh
    OrderBookRefresh = 'O',             // Order Book Refresh
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RefreshMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RefreshMessageType value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
