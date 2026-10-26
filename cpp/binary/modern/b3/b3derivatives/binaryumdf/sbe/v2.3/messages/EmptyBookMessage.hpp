#pragma once

#include "../types/SecurityId.hpp"
#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Offset9Padding3.hpp"
#include "../types/MdEntryTimestamp.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// EmptyBook_9Message
struct EmptyBookMessage {

    SecurityId security_id;
    MatchEventIndicator match_event_indicator;
    Offset9Padding3 offset_9_padding_3;
    MdEntryTimestamp md_entry_timestamp;

    // parse method
    static EmptyBookMessage* parse(std::byte* buffer) {
        return reinterpret_cast<EmptyBookMessage*>(buffer);
    }

    // parse method const
    static const EmptyBookMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const EmptyBookMessage*>(buffer);
    }
};

#pragma pack(pop)
}
