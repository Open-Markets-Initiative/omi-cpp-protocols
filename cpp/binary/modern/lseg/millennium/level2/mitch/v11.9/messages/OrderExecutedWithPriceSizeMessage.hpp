#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/OrderId.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/DisplayQuantity.hpp"
#include "../types/TradeMatchId.hpp"
#include "../types/Printable.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Sent if a displayed order is fully or partially filled at a price that is different from its displayed price.
struct OrderExecutedWithPriceSizeMessage {

    Nanosecond nanosecond;
    OrderId order_id;
    ExecutedQuantity executed_quantity;
    DisplayQuantity display_quantity;
    TradeMatchId trade_match_id;
    Printable printable;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x43;

    // parse method
    static OrderExecutedWithPriceSizeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderExecutedWithPriceSizeMessage*>(buffer);
    }

    // parse method const
    static const OrderExecutedWithPriceSizeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderExecutedWithPriceSizeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderExecutedWithPriceSizeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderExecutedWithPriceSizeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
