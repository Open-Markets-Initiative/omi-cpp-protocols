#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::itch::v1_7 {

// Value identifying sequenced message type
enum class SequencedMessageType : char {
    TimestampSecondsMessage = 'T',                  // Timestamp Seconds Message
    SystemEventMessage = 'S',                       // System Event Message
    PriceTickSizeMessage = 'L',                     // Price Tick Size Message
    OrderbookDirectoryMessage = 'R',                // Orderbook Directory Message
    TradingStateMessage = 'H',                      // Trading State Message
    ShortSellingPriceRestrictionStateMessage = 'Y', // Short Selling Price Restriction State Message
    OrderAddedWithoutAttributesMessage = 'A',       // Order Added Without Attributes Message
    OrderAddedWithAttributesMessage = 'F',          // Order Added With Attributes Message
    OrderExecutedMessage = 'E',                     // Order Executed Message
    OrderDeletedMessage = 'D',                      // Order Deleted Message
    OrderReplacedMessage = 'U',                     // Order Replaced Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SequencedMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SequencedMessageType value);

} // namespace jnx::jnxequities::pts::itch::v1_7
