#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

#pragma pack(push, 1)

// This message is sent to reset the Message Sequence Number at start of day, or in response to failures.
struct SequenceNumberResetMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    ProductId product_id;
    ChannelId channel_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 1;

    // parse method
    static SequenceNumberResetMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SequenceNumberResetMessage*>(buffer);
    }

    // parse method const
    static const SequenceNumberResetMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SequenceNumberResetMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SequenceNumberResetMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SequenceNumberResetMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
