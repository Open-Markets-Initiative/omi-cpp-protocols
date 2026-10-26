#pragma once

#include "../types/Session.hpp"
#include "../types/SequenceNumber.hpp"
#include "../types/MessageCount.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

struct PacketHeader {

    Session session;
    SequenceNumber sequence_number;
    MessageCount message_count;

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
