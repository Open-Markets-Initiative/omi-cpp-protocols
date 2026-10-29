#pragma once

#include "../types/SecurityId.hpp"
#include "../types/AggressorTimestamp.hpp"
#include "../types/ExecId.hpp"
#include "../types/LastQty.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad6.hpp"
#include "../types/LastPx.hpp"
#include "../types/RestingHiddenQty.hpp"
#include "../structs/MessageHeader.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

#pragma pack(push, 1)

// Published whenever an incoming order is executed, carrying information on the execution of that incoming order.
struct ExecutionSummaryMessage {

    SecurityId security_id;
    AggressorTimestamp aggressor_timestamp;
    ExecId exec_id;
    LastQty last_qty;
    AggressorSide aggressor_side;
    TradeCondition trade_condition;
    Pad6 pad_6;
    LastPx last_px;
    RestingHiddenQty resting_hidden_qty;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13202;

    // parse method
    static ExecutionSummaryMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionSummaryMessage*>(buffer);
    }

    // parse method const
    static const ExecutionSummaryMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionSummaryMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ExecutionSummaryMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ExecutionSummaryMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
