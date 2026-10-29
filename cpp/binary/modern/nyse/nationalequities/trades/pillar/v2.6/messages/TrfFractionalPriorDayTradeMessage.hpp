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
#include "../types/PriorDayTime.hpp"
#include "../types/PriorDayTimeNs.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

#pragma pack(push, 1)

// If a TRF participant firm fails to report a trade on the day in which it occurs, the firm may report the trade on a subsequent day by publishing a Prior Day Trade message. New message effective 1/12/26.
struct TrfFractionalPriorDayTradeMessage {

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
    PriorDayTime prior_day_time;
    PriorDayTimeNs prior_day_time_ns;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 213;

    // parse method
    static TrfFractionalPriorDayTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TrfFractionalPriorDayTradeMessage*>(buffer);
    }

    // parse method const
    static const TrfFractionalPriorDayTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TrfFractionalPriorDayTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TrfFractionalPriorDayTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TrfFractionalPriorDayTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
