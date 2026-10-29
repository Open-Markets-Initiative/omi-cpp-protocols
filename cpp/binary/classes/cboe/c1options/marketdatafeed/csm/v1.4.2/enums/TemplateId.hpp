#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// The Template ID is for decoding the message.
enum class TemplateId : std::uint8_t {
    SecurityDefinitionMessage = 13,          // Security Definition Message
    CurrentMarketRefreshMessage = 11,        // Current Market Refresh Message
    MarketDataRefreshMessage = 20,           // Market Data Refresh Message
    CurrentMarketUpdateMessage = 12,         // Current Market Update Message
    RecapUpdateMessage = 21,                 // Recap Update Message
    TickerMessage = 14,                      // Ticker Message
    ExpectedOpeningPriceAndSizeMessage = 15, // Expected Opening Price And Size Message
    IndexValueMessage = 22,                  // Index Value Message
    SettlementValueMessage = 23,             // Settlement Value Message
    SummaryMessage = 24,                     // Summary Message
    MarketDataControlMessage = 25,           // Market Data Control Message
    HeartbeatMessage = 16,                   // Heartbeat Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TemplateId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TemplateId value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
