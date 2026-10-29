#pragma once

#include "../types/Length.hpp"
#include "../types/MessageCount.hpp"
#include "../types/Unit.hpp"
#include "../types/Sequence.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

struct PacketHeader {

    Length length;
    MessageCount message_count;
    Unit unit;
    Sequence sequence;

    // parse method
    static PacketHeader* parse(std::byte* buffer) {
        return reinterpret_cast<PacketHeader*>(buffer);
    }

    // parse method const
    static const PacketHeader* parse(const std::byte* buffer) {
        return reinterpret_cast<const PacketHeader*>(buffer);
    }
};

#pragma pack(pop)
}
