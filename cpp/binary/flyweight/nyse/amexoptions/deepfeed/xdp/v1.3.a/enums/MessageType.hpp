#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// The type of this message
enum class MessageType : std::uint16_t {
    OutrightMarketDepthBuyMessage = 403,         // Outright Market Depth Buy Message
    OutrightMarketDepthSellMessage = 405,        // Outright Market Depth Sell Message
    UnderlyingStatusMessage = 419,               // Underlying Status Message
    OutrightSeriesStatusMessage = 421,           // Outright Series Status Message
    RefreshOutrightMarketDepthBuyMessage = 503,  // Refresh Outright Market Depth Buy Message
    RefreshOutrightMarketDepthSellMessage = 505, // Refresh Outright Market Depth Sell Message
    UnderlyingIndexMappingMessage = 435,         // Underlying Index Mapping Message
    SeriesIndexMappingMessage = 437,             // Series Index Mapping Message
    StreamIdMessage = 455,                       // Stream Id Message
    SequenceNumberResetMessage = 1,              // Sequence Number Reset Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
