#include "OrderCanceledReason.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(OrderCanceledReason value) {
    switch (value) {
        case OrderCanceledReason::UserRequestedCancel: return "User Requested Cancel";
        case OrderCanceledReason::UserLoggedOff: return "User Logged Off";
        case OrderCanceledReason::CanceledBySupervisoryTerminal: return "Canceled By Supervisory Terminal";
        case OrderCanceledReason::ImmediateOrderRemainingQuantityCanceled: return "Immediate Order Remaining Quantity Canceled";
        case OrderCanceledReason::OrderExpiredDuringMatching: return "Order Expired During Matching";
        case OrderCanceledReason::InvalidPrice: return "Invalid Price";
        case OrderCanceledReason::InvalidQuantity: return "Invalid Quantity";
        case OrderCanceledReason::InvalidMinimumQuantity: return "Invalid Minimum Quantity";
        case OrderCanceledReason::InvalidOrderType: return "Invalid Order Type";
        case OrderCanceledReason::InvalidDisplayType: return "Invalid Display Type";
        case OrderCanceledReason::ExceededOrderValueLimit: return "Exceeded Order Value Limit";
        case OrderCanceledReason::ShortSellOrderRestriction: return "Short Sell Order Restriction";
        case OrderCanceledReason::OrderNotAllowedAtThisTime: return "Order Not Allowed At This Time";
        case OrderCanceledReason::FlowControlThrottled: return "Flow Control Throttled";
        case OrderCanceledReason::MarginOrderCanceledDueToMarginRestriction: return "Margin Order Canceled Due To Margin Restriction";
        case OrderCanceledReason::Other: return "Other";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderCanceledReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
