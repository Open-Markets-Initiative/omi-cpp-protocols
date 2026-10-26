#pragma once

#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/CrossNumber.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

#pragma pack(push, 1)

// The Broken Trade Message is sent whenever an execution on NASDAQ is broken. An execution may be broken if it is found to be “clearly erroneous” pursuant to NASDAQ’s Clearly Erroneous Policy. A trade break is final; once a trade is broken, it cannot be reinstated.
struct BrokenTradeOrderExecutedMessage {

    TrackingNumber tracking_number;
    Timestamp timestamp;
    CrossNumber cross_number;
    MatchNumber match_number;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'B';

    // parse method
    static BrokenTradeOrderExecutedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BrokenTradeOrderExecutedMessage*>(buffer);
    }

    // parse method const
    static const BrokenTradeOrderExecutedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BrokenTradeOrderExecutedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const BrokenTradeOrderExecutedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const BrokenTradeOrderExecutedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
