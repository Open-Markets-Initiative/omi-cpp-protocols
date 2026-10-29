#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/FractionalVolume.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/TradeCond3.hpp"
#include "../types/TradeCond4.hpp"
#include "../types/ExecDayTime.hpp"
#include "../types/ExecDayTimeNs.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

#pragma pack(push, 1)

// TRF Fractional Trade Message. New message effective 1/12/26.
struct TrfFractionalTradeMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    TradeId trade_id;
    Price price;
    FractionalVolume fractional_volume;
    TradeCond1 trade_cond_1;
    TradeCond2 trade_cond_2;
    TradeCond3 trade_cond_3;
    TradeCond4 trade_cond_4;
    ExecDayTime exec_day_time;
    ExecDayTimeNs exec_day_time_ns;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 210;

    // parse method
    static TrfFractionalTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TrfFractionalTradeMessage*>(buffer);
    }

    // parse method const
    static const TrfFractionalTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TrfFractionalTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TrfFractionalTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TrfFractionalTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
