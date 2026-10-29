#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Reason the order was rejected
enum class OrderRejectedReason : char {
    TradingHalt = 'H',                          // Trading Halt
    InvalidOrderBookIdentifier = 'S',           // Invalid Order Book Identifier
    InvalidPrice = 'X',                         // Invalid Price
    InvalidQuantity = 'Z',                      // Invalid Quantity
    InvalidMinimumQuantity = 'N',               // Invalid Minimum Quantity
    InvalidOrderType = 'Y',                     // Invalid Order Type
    InvalidDisplayType = 'D',                   // Invalid Display Type
    ExceededOrderValueLimit = 'V',              // Exceeded Order Value Limit
    ShortSellOrderRestriction = 'i',            // Short Sell Order Restriction
    OrderNotAllowedAtThisTime = 'R',            // Order Not Allowed At This Time
    FlowControlThrottled = 'F',                 // Flow Control Throttled
    InvalidMarginSpecification = 'G',           // Invalid Margin Specification
    MpidNotAllowedForThisPort = 'L',            // Mpid Not Allowed For This Port
    NoPermissionToEnterOrderOnGivenBoard = 'c', // No Permission To Enter Order On Given Board
    Other = 'O',                                // Other
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderRejectedReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderRejectedReason value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
