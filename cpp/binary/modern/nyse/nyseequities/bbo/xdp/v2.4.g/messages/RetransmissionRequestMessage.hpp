#pragma once

#include "../types/BeginSeqNum.hpp"
#include "../types/EndSeqNum.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

#pragma pack(push, 1)

// Clients who have experienced a sequence number gap and need a retransmission of the missed messages should send a Retransmission Request message via TCP to the Request Controller. A Request Response message will be sent over the TCP connection back to the client, and if the request was valid, the requested message(s) will be re-published over the relevant Retransmission multicast channel.
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
