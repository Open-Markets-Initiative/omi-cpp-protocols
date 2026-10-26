#pragma once

#include "../bitfields/MatchEventIndicator.hpp"
#include "../types/Offset1Padding3.hpp"
#include "../types/MdEntryTimestamp.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

#pragma pack(push, 1)

// ChannelReset_11Message
struct ChannelReset11Message {

    MatchEventIndicator match_event_indicator;
    Offset1Padding3 offset_1_padding_3;
    MdEntryTimestamp md_entry_timestamp;

    // parse method
    static ChannelReset11Message* parse(std::byte* buffer) {
        return reinterpret_cast<ChannelReset11Message*>(buffer);
    }

    // parse method const
    static const ChannelReset11Message* parse(const std::byte* buffer) {
        return reinterpret_cast<const ChannelReset11Message*>(buffer);
    }
};

#pragma pack(pop)
}
