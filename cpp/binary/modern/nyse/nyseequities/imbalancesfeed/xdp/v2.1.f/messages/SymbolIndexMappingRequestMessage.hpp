#pragma once

#include "../types/SymbolIndex.hpp"
#include "../types/SourceId.hpp"
#include "../types/ProductId.hpp"
#include "../types/ChannelId.hpp"
#include "../types/RetransmitMethod.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

#pragma pack(push, 1)

// This message is sent by clients via TCP/IP requesting the Symbol Index Mapping messages for one or all symbols in a specified channel.
struct SymbolIndexMappingRequestMessage {

    SymbolIndex symbol_index;
    SourceId source_id;
    ProductId product_id;
    ChannelId channel_id;
    RetransmitMethod retransmit_method;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13;

    // parse method
    static SymbolIndexMappingRequestMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SymbolIndexMappingRequestMessage*>(buffer);
    }

    // parse method const
    static const SymbolIndexMappingRequestMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SymbolIndexMappingRequestMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SymbolIndexMappingRequestMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const SymbolIndexMappingRequestMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
