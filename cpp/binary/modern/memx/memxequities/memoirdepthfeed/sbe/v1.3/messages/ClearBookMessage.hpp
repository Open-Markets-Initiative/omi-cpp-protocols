#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// ClearBookMessage
struct ClearBookMessage {

    Timestamp timestamp;
    SecurityId security_id;

    // parse method
    static ClearBookMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ClearBookMessage*>(buffer);
    }

    // parse method const
    static const ClearBookMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ClearBookMessage*>(buffer);
    }
};

#pragma pack(pop)
}
