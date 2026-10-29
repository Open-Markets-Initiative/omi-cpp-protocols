#pragma once

#include "../types/FromSeqNo.hpp"
#include "../types/Count.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

#pragma pack(push, 1)

// NotAppliedMessage
struct NotAppliedMessage {

    FromSeqNo from_seq_no;
    Count count;

    // parse method
    static NotAppliedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NotAppliedMessage*>(buffer);
    }

    // parse method const
    static const NotAppliedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NotAppliedMessage*>(buffer);
    }
};

#pragma pack(pop)
}
