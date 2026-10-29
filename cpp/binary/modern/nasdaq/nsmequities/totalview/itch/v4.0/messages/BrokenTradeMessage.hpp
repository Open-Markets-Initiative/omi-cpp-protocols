#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/MatchNumber.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

#pragma pack(push, 1)

// The Broken Trade Message is sent whenever an execution on NASDAQ is broken.
struct BrokenTradeMessage {

    Nanoseconds nanoseconds;
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
