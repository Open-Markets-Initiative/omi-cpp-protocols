#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad6.hpp"
#include "../types/NoMdEntries.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct TradeReversal {

    SecurityId security_id;
    TransactTime transact_time;
    TrdMatchId trd_match_id;
    LastQty last_qty;
    LastPx last_px;
    TrdRegTsExecutionTime trd_reg_ts_execution_time;
    TradeCondition trade_condition;
    Pad6 pad6;
    NoMdEntries no_md_entries;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13200;

    // parse method
    static TradeReversal* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReversal*>(buffer);
    }

    // parse method const
    static const TradeReversal* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReversal*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeReversal* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const TradeReversal*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
