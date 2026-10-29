#pragma once

#include "../types/SymbolIndex.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

#pragma pack(push, 1)

// Clients who have experienced a failure and need a refresh of the state of one or all symbols in a specific channel should send a Retransmission Request message via TCP to the Request Controller. A Request Response message will be sent over the TCP connection back to the client, and if the request was valid, the requested message(s) will be published over the relevant Refresh multicast channel.
struct RefreshRequestMessage {

    SymbolIndex symbol_index;
    SourceId source_id;
    ProductId product_id;
    ChannelId channel_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 15;

    // parse method
    static RefreshRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RefreshRequestMessage*>(buffer);
    }

    // parse method const
    static const RefreshRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RefreshRequestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RefreshRequestMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RefreshRequestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
