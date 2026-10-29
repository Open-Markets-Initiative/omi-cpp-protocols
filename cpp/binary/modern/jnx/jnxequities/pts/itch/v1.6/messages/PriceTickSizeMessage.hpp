#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/PriceTickSizeTableId.hpp"
#include "../types/PriceTickSize.hpp"
#include "../types/PriceStart.hpp"
#include "../structs/MessageHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

#pragma pack(push, 1)

// Price Tick Size Messages define a set of price tick size tables.
struct PriceTickSizeMessage {

    Nanoseconds nanoseconds;
    PriceTickSizeTableId price_tick_size_table_id;
    PriceTickSize price_tick_size;
    PriceStart price_start;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'L';

    // parse method
    static PriceTickSizeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<PriceTickSizeMessage*>(buffer);
    }

    // parse method const
    static const PriceTickSizeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const PriceTickSizeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const PriceTickSizeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const PriceTickSizeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
