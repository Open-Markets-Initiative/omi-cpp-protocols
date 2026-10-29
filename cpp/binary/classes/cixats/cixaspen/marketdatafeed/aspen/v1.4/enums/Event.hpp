#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Session state event code
enum class Event : char {
    StartOfSession = 'O',         // Start Of Session
    MarketAcceptingOrders = 'S',  // Market Accepting Orders
    MarketOpenForTrading = 'Q',   // Market Open For Trading
    MarketClosedForTrading = 'E', // Market Closed For Trading
    EndOfSession = 'C',           // End Of Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Event value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Event value);

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
