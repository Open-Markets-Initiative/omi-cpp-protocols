#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// OrderExecutedMessage
struct OrderExecutedMessage {

    Timestamp timestamp;
    SecurityId security_id;
    OrderId order_id;
    TradeId trade_id;
    Quantity quantity;
    Price price;

    // parse method
    static OrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
