#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OriginalTradeId.hpp"
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

// In the event that an earlier trade has been reported with one or multiple fields in error, a Trade Correction message is sent.
struct TradeCorrectionMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    OriginalTradeId original_trade_id;
    TradeId trade_id;
    Price price;
    Volume volume;
    TradeCond1 trade_cond_1;
    TradeCond2 trade_cond_2;
    TradeCond3 trade_cond_3;
    TradeCond4 trade_cond_4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 222;

    // parse method
    static TradeCorrectionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCorrectionMessage*>(buffer);
    }

    // parse method const
    static const TradeCorrectionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCorrectionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCorrectionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeCorrectionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
