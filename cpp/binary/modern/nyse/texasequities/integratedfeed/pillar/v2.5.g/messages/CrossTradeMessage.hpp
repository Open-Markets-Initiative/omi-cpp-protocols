#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/CrossId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/CrossType.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// A Cross Trade message is published on completion of a crossing auction.
struct CrossTradeMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    CrossId cross_id;
    Price price;
    Volume volume;
    CrossType cross_type;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 111;

    // parse method
    static CrossTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CrossTradeMessage*>(buffer);
    }

    // parse method const
    static const CrossTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CrossTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CrossTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
