#pragma once

#include "../types/StockLocate.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::psxequities::totalview::itch::v5_0 {

#pragma pack(push, 1)

// The Broken Trade Message is sent whenever an execution on Nasdaq PSX is broken. An execution may be broken if it is found to be “clearly erroneous” pursuant to Nasdaq’s Clearly Erroneous Policy. A trade break is final; once a trade is broken, it cannot be reinstated.
struct BrokenTradeMessage {

    StockLocate stock_locate;
    TrackingNumber tracking_number;
    Timestamp timestamp;
    MatchNumber match_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'B';

    // parse method
    static BrokenTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BrokenTradeMessage*>(buffer);
    }

    // parse method const
    static const BrokenTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BrokenTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const BrokenTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const BrokenTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
