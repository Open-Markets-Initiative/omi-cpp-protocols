#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PositionChange.hpp"
#include "../types/Side.hpp"
#include "../types/Reserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// A Modify Order message is sent when the price or volume of an order is changed.
struct ModifyOrderMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OrderId order_id;
    Price price;
    Volume volume;
    PositionChange position_change;
    Side side;
    Reserved1 reserved_1;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 101;

    // parse method
    static ModifyOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ModifyOrderMessage*>(buffer);
    }

    // parse method const
    static const ModifyOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ModifyOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ModifyOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ModifyOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
