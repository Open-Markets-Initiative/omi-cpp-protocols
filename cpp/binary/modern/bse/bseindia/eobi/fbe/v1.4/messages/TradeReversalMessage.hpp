#pragma once

#include "../types/SecurityId.hpp"
#include "../types/TransactTime.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/Pad4.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../types/TrdRegTsExecutionTime.hpp"
#include "../types/NoMdEntries.hpp"
#include "../types/Pad7.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published when a trade is reversed.
struct TradeReversalMessage {

    SecurityId security_id;
    TransactTime transact_time;
    TrdMatchId trd_match_id;
    Pad4 pad_4;
    LastQty last_qty;
    LastPx last_px;
    TrdRegTsExecutionTime trd_reg_ts_execution_time;
    NoMdEntries no_md_entries;
    Pad7 pad_7;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13200;

    // parse method
    static TradeReversalMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeReversalMessage*>(buffer);
    }

    // parse method const
    static const TradeReversalMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeReversalMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeReversalMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeReversalMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
