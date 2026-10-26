#pragma once

#include "../types/SequenceNumber.hpp"
#include "../types/MatchingEngineId.hpp"
#include "../types/SequencedMessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

struct SequencedDataPacket {

    SequenceNumber sequence_number;
    MatchingEngineId matching_engine_id;
    SequencedMessageType sequenced_message_type;

    // parse method
    static SequencedDataPacket* parse(std::byte* buffer) {
        return reinterpret_cast<SequencedDataPacket*>(buffer);
    }

    // parse method const
    static const SequencedDataPacket* parse(const std::byte* buffer) {
        return reinterpret_cast<const SequencedDataPacket*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SequencedDataPacket* parse(const EsesmPacketHeader* header) {
        return reinterpret_cast<const SequencedDataPacket*>(reinterpret_cast<const std::byte*>(header) + sizeof(EsesmPacketHeader));
    }
};

#pragma pack(pop)
}
