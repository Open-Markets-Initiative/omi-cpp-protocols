#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// In the event that an earlier trade has been reported in error, a Trade Cancel message is sent.
struct TradeCancelMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    TradeId trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 112;

    // parse method
    static TradeCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancelMessage*>(buffer);
    }

    // parse method const
    static const TradeCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCancelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
