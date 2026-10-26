#pragma once

#include "../types/NextSeqNo.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// Sequence_2Message
struct SequenceMessage {

    NextSeqNo next_seq_no;

    // parse method
    static SequenceMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SequenceMessage*>(buffer);
    }

    // parse method const
    static const SequenceMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SequenceMessage*>(buffer);
    }
};

#pragma pack(pop)
}
