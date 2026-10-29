#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OriginalTradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

#pragma pack(push, 1)

// In the event that an earlier trade has been reported in error, a Trade Cancel message is sent.
struct TradeCancelMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OriginalTradeId original_trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 221;

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
