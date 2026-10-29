#pragma once

#include "../types/BeginSeqNum.hpp"
#include "../types/EndSeqNum.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

#pragma pack(push, 1)

// This message will be sent over the Retransmission multicast channels to inform clients of unavailability of a range of messages (or part of a range) for which they may have requested a retransmission.
struct MessageUnavailableMessage {

    BeginSeqNum begin_seq_num;
    EndSeqNum end_seq_num;
    ProductId product_id;
    ChannelId channel_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 31;

    // parse method
    static MessageUnavailableMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MessageUnavailableMessage*>(buffer);
    }

    // parse method const
    static const MessageUnavailableMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MessageUnavailableMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MessageUnavailableMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MessageUnavailableMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
