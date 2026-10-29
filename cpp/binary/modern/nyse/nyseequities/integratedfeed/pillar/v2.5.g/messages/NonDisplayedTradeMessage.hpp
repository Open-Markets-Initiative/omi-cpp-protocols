#pragma once

#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/TradeCond3.hpp"
#include "../types/TradeCond4.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

#pragma pack(push, 1)

// A Non Displayed Trade message is sent as a result of a match between two non-displayed orders.
struct NonDisplayedTradeMessage {

    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    TradeId trade_id;
    Price price;
    Volume volume;
    PrintableFlag printable_flag;
    TradeCond1 trade_cond_1;
    TradeCond2 trade_cond_2;
    TradeCond3 trade_cond_3;
    TradeCond4 trade_cond_4;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 110;

    // parse method
    static NonDisplayedTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NonDisplayedTradeMessage*>(buffer);
    }

    // parse method const
    static const NonDisplayedTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NonDisplayedTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NonDisplayedTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NonDisplayedTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
