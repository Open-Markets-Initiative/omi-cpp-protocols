#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/TickSize.hpp"
#include "../types/PriceFrom.hpp"
#include "../types/PriceTo.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Information on a tick size for a price range.
struct TickSizeTableEntry {

    Nanoseconds nanoseconds;
    OrderBookId order_book_id;
    TickSize tick_size;
    PriceFrom price_from;
    PriceTo price_to;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static TickSizeTableEntry* parse(std::byte* buffer) {
        return reinterpret_cast<TickSizeTableEntry*>(buffer);
    }

    // parse method const
    static const TickSizeTableEntry* parse(const std::byte* buffer) {
        return reinterpret_cast<const TickSizeTableEntry*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TickSizeTableEntry* parse(const MessageHeader* header) {
        return reinterpret_cast<const TickSizeTableEntry*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
