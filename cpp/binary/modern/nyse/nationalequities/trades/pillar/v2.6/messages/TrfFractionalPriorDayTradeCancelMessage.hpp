#pragma once

#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/FractionalVolume.hpp"
#include "../types/PriorDayTime.hpp"
#include "../types/PriorDayTimeNs.hpp"
#include "../structs/MessageHeader.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

#pragma pack(push, 1)

// If a TRF participant firm discovers that it has reported a trade with an inaccurate price or volume on a previous day, the firm may correct the trade on a subsequent day by publishing a Prior Day Trade Cancel message, followed by a Prior Day Trade. New message effective 1/12/26.
struct TrfFractionalPriorDayTradeCancelMessage {

    SourceTime source_time;
    SourceTimeNs source_time_ns;
    SymbolIndex symbol_index;
    SymbolSeqNum symbol_seq_num;
    TradeId trade_id;
    Price price;
    FractionalVolume fractional_volume;
    PriorDayTime prior_day_time;
    PriorDayTimeNs prior_day_time_ns;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 214;

    // parse method
    static TrfFractionalPriorDayTradeCancelMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TrfFractionalPriorDayTradeCancelMessage*>(buffer);
    }

    // parse method const
    static const TrfFractionalPriorDayTradeCancelMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TrfFractionalPriorDayTradeCancelMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TrfFractionalPriorDayTradeCancelMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TrfFractionalPriorDayTradeCancelMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
