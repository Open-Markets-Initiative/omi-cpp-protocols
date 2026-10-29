#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/NewOrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/Side.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// A Replace Order message is published when a cancel/replace order is received and executed.
struct ReplaceOrderMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OrderId order_id;
    NewOrderId new_order_id;
    Price price;
    Volume volume;
    Side side;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 104;

    // parse method
    static ReplaceOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ReplaceOrderMessage*>(buffer);
    }

    // parse method const
    static const ReplaceOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ReplaceOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ReplaceOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ReplaceOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
