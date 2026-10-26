#pragma once

#include "../types/TimeSeconds.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides information about the time of processing on the Trading Server to the nearest second. Always delivered at the time the information is generated, except for Reset and Communication Control. Only one tag is delivered per process and stored at the top of the first packet.
struct SecondsTimestampMessage {

    TimeSeconds time_seconds;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'T';

    // parse method
    static SecondsTimestampMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecondsTimestampMessage*>(buffer);
    }

    // parse method const
    static const SecondsTimestampMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecondsTimestampMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecondsTimestampMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SecondsTimestampMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
