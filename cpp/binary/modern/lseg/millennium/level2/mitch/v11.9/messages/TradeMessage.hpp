#pragma once

#include "../types/Nanosecond.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../types/TradeMatchId.hpp"
#include "../types/CrossType.hpp"
#include "../types/SubBook.hpp"
#include "../bitfields/PtModFlags.hpp"
#include "../structs/MessageHeader.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

#pragma pack(push, 1)

// Sent if a non-display order is fully or partially filled.
struct TradeMessage {

    Nanosecond nanosecond;
    ExecutedQuantity executed_quantity;
    InstrumentId instrument_id;
    ReservedA reserved_a;
    ReservedB reserved_b;
    Price price;
    TradeMatchId trade_match_id;
    CrossType cross_type;
    SubBook sub_book;
    PtModFlags pt_mod_flags;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x50;

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
