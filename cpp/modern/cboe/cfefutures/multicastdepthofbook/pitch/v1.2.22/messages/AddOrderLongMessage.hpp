#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/OrderId.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/QuantityLong.hpp"
#include "../types/Symbol.hpp"
#include "../types/PriceLong.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// An Add Order message represents a newly accepted visible order on the CFE book.
struct AddOrderLongMessage {

    TimeOffset time_offset;
    OrderId order_id;
    SideIndicator side_indicator;
    QuantityLong quantity_long;
    Symbol symbol;
    PriceLong price_long;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x21;

    // parse method
    static AddOrderLongMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderLongMessage*>(buffer);
    }

    // parse method const
    static const AddOrderLongMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderLongMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderLongMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderLongMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
