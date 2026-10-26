#pragma once

#include "../types/BeginSeqNum.hpp"
#include "../types/EndSeqNum.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

#pragma pack(push, 1)

// Sent by clients via TCP/IP to request retransmission of missed messages.
struct RetransmissionRequestMessage {

    BeginSeqNum begin_seq_num;
    EndSeqNum end_seq_num;
    SourceId source_id;
    ProductId product_id;
    ChannelId channel_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 10;

    // parse method
    static RetransmissionRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RetransmissionRequestMessage*>(buffer);
    }

    // parse method const
    static const RetransmissionRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RetransmissionRequestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RetransmissionRequestMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RetransmissionRequestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
