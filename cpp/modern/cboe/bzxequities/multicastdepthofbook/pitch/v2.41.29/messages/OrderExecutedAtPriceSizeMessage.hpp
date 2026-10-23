#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/RemainingQuantity.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// Order Executed at Price/Size messages are sent when a visible order on the Cboe book is executed in whole or in part at a different price than the limit price on the original Add Order message or the limit order price in the latest Modify Order message referencing the Order Id.
struct OrderExecutedAtPriceSizeMessage {

    TimeOffset time_offset;
    OrderId order_id;
    ExecutedQuantity executed_quantity;
    RemainingQuantity remaining_quantity;
    ExecutionId execution_id;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x24;

    // parse method
    static OrderExecutedAtPriceSizeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedAtPriceSizeMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedAtPriceSizeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedAtPriceSizeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedAtPriceSizeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedAtPriceSizeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
