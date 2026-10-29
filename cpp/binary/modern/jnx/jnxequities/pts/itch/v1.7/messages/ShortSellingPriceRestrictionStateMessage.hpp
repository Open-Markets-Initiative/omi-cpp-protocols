#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/Group.hpp"
#include "../types/ShortSellingState.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

#pragma pack(push, 1)

// Short Selling Price Restriction State Message indicates the current short selling price restriction state of an orderbook.
struct ShortSellingPriceRestrictionStateMessage {

    Nanoseconds nanoseconds;
    OrderbookId orderbook_id;
    Group group;
    ShortSellingState short_selling_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Y';

    // parse method
    static ShortSellingPriceRestrictionStateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ShortSellingPriceRestrictionStateMessage*>(buffer);
    }

    // parse method const
    static const ShortSellingPriceRestrictionStateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ShortSellingPriceRestrictionStateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ShortSellingPriceRestrictionStateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ShortSellingPriceRestrictionStateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
