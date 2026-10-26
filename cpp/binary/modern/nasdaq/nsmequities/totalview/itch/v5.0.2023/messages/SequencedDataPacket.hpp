#pragma once

#include "../types/SequencedMessageType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

#pragma pack(push, 1)

// The Sequenced Data Packets act as an envelope to carry the actual sequenced data messages that are transferred from the server to the client. Each Sequenced Data Packet carries one message from the higher-lever protocol
struct SequencedDataPacket {

    SequencedMessageType sequenced_message_type;

    // parse method
    static SequencedDataPacket* parse(std::byte* buffer) {
        return reinterpret_cast<SequencedDataPacket*>(buffer);
    }

    // parse method const
    static const SequencedDataPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const SequencedDataPacket*>(buffer);
    }
};

#pragma pack(pop)
}
