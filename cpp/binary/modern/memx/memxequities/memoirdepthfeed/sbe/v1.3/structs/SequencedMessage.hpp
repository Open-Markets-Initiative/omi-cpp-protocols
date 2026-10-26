#pragma once

#include "../types/MessageCount.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

struct SequencedMessage {

    MessageCount message_count;

    // parse method
    static SequencedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SequencedMessage*>(buffer);
    }

    // parse method const
    static const SequencedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SequencedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
