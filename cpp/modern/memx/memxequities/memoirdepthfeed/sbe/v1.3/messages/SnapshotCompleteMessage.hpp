#pragma once

#include "../types/Timestamp.hpp"
#include "../types/AsOfSequenceNumber.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// SnapshotCompleteMessage
struct SnapshotCompleteMessage {

    Timestamp timestamp;
    AsOfSequenceNumber as_of_sequence_number;

    // parse method
    static SnapshotCompleteMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotCompleteMessage*>(buffer);
    }

    // parse method const
    static const SnapshotCompleteMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotCompleteMessage*>(buffer);
    }
};

#pragma pack(pop)
}
