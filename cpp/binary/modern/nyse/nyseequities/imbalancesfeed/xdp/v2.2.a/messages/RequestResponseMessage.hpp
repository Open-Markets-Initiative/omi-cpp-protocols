#pragma once

#include "../types/RequestSeqNum.hpp"
#include "../types/BeginSeqNum.hpp"
#include "../types/EndSeqNum.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../types/Status.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

#pragma pack(push, 1)

// This message will be sent immediately via TCP/IP in response to the client’s request for retransmission, refresh or Symbol Mapping messages.
struct RequestResponseMessage {

    RequestSeqNum request_seq_num;
    BeginSeqNum begin_seq_num;
    EndSeqNum end_seq_num;
    SourceId source_id;
    ProductId product_id;
    ChannelId channel_id;
    Status status;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 11;

    // parse method
    static RequestResponseMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RequestResponseMessage*>(buffer);
    }

    // parse method const
    static const RequestResponseMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RequestResponseMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RequestResponseMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RequestResponseMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
