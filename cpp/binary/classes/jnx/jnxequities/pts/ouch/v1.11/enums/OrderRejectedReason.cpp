#include "OrderRejectedReason.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(OrderRejectedReason value) {
    switch (value) {
        case OrderRejectedReason::TradingHalt: return "Trading Halt";
        case OrderRejectedReason::InvalidOrderBookIdentifier: return "Invalid Order Book Identifier";
        case OrderRejectedReason::InvalidPrice: return "Invalid Price";
        case OrderRejectedReason::InvalidQuantity: return "Invalid Quantity";
        case OrderRejectedReason::InvalidMinimumQuantity: return "Invalid Minimum Quantity";
        case OrderRejectedReason::InvalidOrderType: return "Invalid Order Type";
        case OrderRejectedReason::InvalidDisplayType: return "Invalid Display Type";
        case OrderRejectedReason::ExceededOrderValueLimit: return "Exceeded Order Value Limit";
        case OrderRejectedReason::ShortSellOrderRestriction: return "Short Sell Order Restriction";
        case OrderRejectedReason::OrderNotAllowedAtThisTime: return "Order Not Allowed At This Time";
        case OrderRejectedReason::FlowControlThrottled: return "Flow Control Throttled";
        case OrderRejectedReason::InvalidMarginSpecification: return "Invalid Margin Specification";
        case OrderRejectedReason::MpidNotAllowedForThisPort: return "Mpid Not Allowed For This Port";
        case OrderRejectedReason::NoPermissionToEnterOrderOnGivenBoard: return "No Permission To Enter Order On Given Board";
        case OrderRejectedReason::Other: return "Other";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OrderRejectedReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
