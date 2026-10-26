#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// OrderAddedMessage
struct OrderAddedMessage {

    Timestamp timestamp;
    SecurityId security_id;
    OrderId order_id;
    Side side;
    Quantity quantity;
    Price price;

    // parse method
    static OrderAddedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderAddedMessage*>(buffer);
    }

    // parse method const
    static const OrderAddedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderAddedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
