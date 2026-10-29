#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Reason order was reduced or canceled
enum class OrderCanceledReason : char {
    UserRequestedCancel = 'U',                       // User Requested Cancel
    UserLoggedOff = 'L',                             // User Logged Off
    CanceledBySupervisoryTerminal = 'S',             // Canceled By Supervisory Terminal
    ImmediateOrderRemainingQuantityCanceled = 'I',   // Immediate Order Remaining Quantity Canceled
    OrderExpiredDuringMatching = 'M',                // Order Expired During Matching
    InvalidPrice = 'X',                              // Invalid Price
    InvalidQuantity = 'Z',                           // Invalid Quantity
    InvalidMinimumQuantity = 'N',                    // Invalid Minimum Quantity
    InvalidOrderType = 'Y',                          // Invalid Order Type
    InvalidDisplayType = 'D',                        // Invalid Display Type
    ExceededOrderValueLimit = 'V',                   // Exceeded Order Value Limit
    ShortSellOrderRestriction = 'i',                 // Short Sell Order Restriction
    OrderNotAllowedAtThisTime = 'R',                 // Order Not Allowed At This Time
    FlowControlThrottled = 'F',                      // Flow Control Throttled
    MarginOrderCanceledDueToMarginRestriction = 'G', // Margin Order Canceled Due To Margin Restriction
    Other = 'O',                                     // Other
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderCanceledReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderCanceledReason value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
