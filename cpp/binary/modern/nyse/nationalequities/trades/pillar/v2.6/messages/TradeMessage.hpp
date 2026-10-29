#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/TradeCond3.hpp"
#include "../types/TradeCond4.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

#pragma pack(push, 1)

// A Trade message is sent when there is an execution on the order book.
struct TradeMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    TradeId trade_id;
    Price price;
    Volume volume;
    TradeCond1 trade_cond_1;
    TradeCond2 trade_cond_2;
    TradeCond3 trade_cond_3;
    TradeCond4 trade_cond_4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 220;

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
