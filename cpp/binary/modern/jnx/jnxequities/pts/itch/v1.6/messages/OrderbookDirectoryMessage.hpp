#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderbookId.hpp"
#include "../types/OrderbookCode.hpp"
#include "../types/Group.hpp"
#include "../types/RoundLotSize.hpp"
#include "../types/PriceTickSizeTableId.hpp"
#include "../types/PriceDecimals.hpp"
#include "../types/UpperPriceLimit.hpp"
#include "../types/LowerPriceLimit.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

#pragma pack(push, 1)

// Orderbook Directory Messages provide information about orderbooks available in the Japannext PTS execution system.
struct OrderbookDirectoryMessage {

    Nanoseconds nanoseconds;
    OrderbookId orderbook_id;
    OrderbookCode orderbook_code;
    Group group;
    RoundLotSize round_lot_size;
    PriceTickSizeTableId price_tick_size_table_id;
    PriceDecimals price_decimals;
    UpperPriceLimit upper_price_limit;
    LowerPriceLimit lower_price_limit;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'R';

    // parse method
    static OrderbookDirectoryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderbookDirectoryMessage*>(buffer);
    }

    // parse method const
    static const OrderbookDirectoryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderbookDirectoryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderbookDirectoryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderbookDirectoryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
