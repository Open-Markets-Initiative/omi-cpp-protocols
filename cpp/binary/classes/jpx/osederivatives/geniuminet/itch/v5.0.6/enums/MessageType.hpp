#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Code identifying this message type
enum class MessageType : char {
    SecondsMessage = 'T',                // Seconds Message
    OrderBookDirectory = 'R',            // Order Book Directory
    CombinationOrderbookLeg = 'M',       // Combination Orderbook Leg
    TickSizeTableEntry = 'L',            // Tick Size Table Entry
    SystemEventMessage = 'S',            // System Event Message
    OrderBookStateMessage = 'O',         // Order Book State Message
    AddOrderNoMpid = 'A',                // Add Order No Mpid
    AddOrderWithMpid = 'F',              // Add Order With Mpid
    OrderExecutedMessage = 'E',          // Order Executed Message
    OrderExecutedWithPriceMessage = 'C', // Order Executed With Price Message
    OrderReplaceMessage = 'U',           // Order Replace Message
    OrderDeleteMessage = 'D',            // Order Delete Message
    TradeMessage = 'P',                  // Trade Message
    EquilibriumPriceUpdate = 'Z',        // Equilibrium Price Update
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MessageType value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
