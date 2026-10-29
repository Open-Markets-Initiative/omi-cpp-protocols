#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/RemainingQuantity.hpp"
#include "../types/ExecutionId.hpp"
#include "../types/PriceBinaryLongPrice8.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

#pragma pack(push, 1)

// Order Executed at Price/Size
struct OrderExecutedAtPriceSizeMessage {

    TimeOffset time_offset;
    OrderId order_id;
    ExecutedQuantity executed_quantity;
    RemainingQuantity remaining_quantity;
    ExecutionId execution_id;
    PriceBinaryLongPrice8 price_binary_long_price_8;

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
