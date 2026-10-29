#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

#pragma pack(push, 1)

// A Delete Order message is published when an order is taken off of the book.
struct DeleteOrderMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OrderId order_id;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 102;

    // parse method
    static DeleteOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<DeleteOrderMessage*>(buffer);
    }

    // parse method const
    static const DeleteOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeleteOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const DeleteOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const DeleteOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
