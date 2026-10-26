#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Quantity.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// OrderReducedMessage
struct OrderReducedMessage {

    Timestamp timestamp;
    SecurityId security_id;
    OrderId order_id;
    Quantity quantity;

    // parse method
    static OrderReducedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderReducedMessage*>(buffer);
    }

    // parse method const
    static const OrderReducedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderReducedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
