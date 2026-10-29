#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/Side.hpp"
#include "../types/FirmId.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

#pragma pack(push, 1)

// An Add Order message is published when a new visible order has been received and added to the book.
struct AddOrderMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OrderId order_id;
    Price price;
    Volume volume;
    Side side;
    FirmId firm_id;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 100;

    // parse method
    static AddOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
