#pragma once

#include "../types/TimeOffset.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgaequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// The Unit Clear message instructs feed recipients to clear all orders for the Cboe book in the unit specified in the Sequenced Unit Header
struct UnitClearMessage {

    TimeOffset time_offset;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x97;

    // parse method
    static UnitClearMessage* parse(std::byte* buffer) {
        return reinterpret_cast<UnitClearMessage*>(buffer);
    }

    // parse method const
    static const UnitClearMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnitClearMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const UnitClearMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const UnitClearMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
