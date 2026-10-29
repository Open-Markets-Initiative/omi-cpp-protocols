#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/MatchType.hpp"
#include "../types/MatchSubType.hpp"
#include "../types/Pad6.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

#pragma pack(push, 1)

// 
struct TradeReport {

    SecurityId security_id;
    TransactTime transact_time;
    TrdMatchId trd_match_id;
    LastQty last_qty;
    LastPx last_px;
    MatchType match_type;
    MatchSubType match_sub_type;
    Pad6 pad6;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13201;

    // parse method
    static TradeReport* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReport*>(buffer);
    }

    // parse method const
    static const TradeReport* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReport*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeReport* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const TradeReport*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
