#pragma once

#include "../types/TimeMicroseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Volume.hpp"
#include "../types/MatchId.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides information about registered orders in case of Zaraba execution. Delivered when an execution occurs in Zaraba.
struct OrderExecutedMessage {

    TimeMicroseconds time_microseconds;
    OrderId order_id;
    Side side;
    Volume volume;
    MatchId match_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'E';

    // parse method
    static OrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
