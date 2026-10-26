#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/OrderId.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// OrderDeletedMessage
struct OrderDeletedMessage {

    Timestamp timestamp;
    SecurityId security_id;
    OrderId order_id;

    // parse method
    static OrderDeletedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeletedMessage*>(buffer);
    }

    // parse method const
    static const OrderDeletedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeletedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
