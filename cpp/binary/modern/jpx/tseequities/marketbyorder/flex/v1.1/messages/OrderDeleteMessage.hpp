#pragma once

#include "../types/TimeMicroseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/ModificationFlag.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides information about order deletion from the order book. Delivered when an order is deleted via a cancel order or a modification order or when a registered order expires.
struct OrderDeleteMessage {

    TimeMicroseconds time_microseconds;
    OrderId order_id;
    Side side;
    ModificationFlag modification_flag;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static OrderDeleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeleteMessage*>(buffer);
    }

    // parse method const
    static const OrderDeleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeleteMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDeleteMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderDeleteMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
