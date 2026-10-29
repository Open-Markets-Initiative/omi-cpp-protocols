#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume4.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/Reserved2.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

#pragma pack(push, 1)

// The Refresh Complex Trade message is sent in the event no Complex Trade messages are published for the symbol for 2 consecutive minutes.
struct RefreshComplexTradeMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    ComplexIndex complex_index;
    SymbolSeqNum symbol_seq_num;
    TradeId trade_id;
    Price price;
    Volume4 volume_4;
    TradeCond1 trade_cond_1;
    TradeCond2 trade_cond_2;
    Reserved2 reserved_2;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 513;

    // parse method
    static RefreshComplexTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<RefreshComplexTradeMessage*>(buffer);
    }

    // parse method const
    static const RefreshComplexTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const RefreshComplexTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const RefreshComplexTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const RefreshComplexTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
