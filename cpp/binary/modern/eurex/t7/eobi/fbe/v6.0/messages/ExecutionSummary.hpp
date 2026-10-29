#pragma once

#include "../types/SecurityId.hpp"
#include "../types/AggressorTime.hpp"
#include "../types/RequestTime.hpp"
#include "../types/ExecId.hpp"
#include "../types/LastQty.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/Pad2.hpp"
#include "../types/LastPx.hpp"
#include "../types/RestingHiddenQty.hpp"
#include "../types/RestingCxlQty.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct ExecutionSummary {

    SecurityId security_id;
    AggressorTime aggressor_time;
    RequestTime request_time;
    ExecId exec_id;
    LastQty last_qty;
    AggressorSide aggressor_side;
    TradeCondition trade_condition;
    Pad2 pad2;
    LastPx last_px;
    RestingHiddenQty resting_hidden_qty;
    RestingCxlQty resting_cxl_qty;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13202;

    // parse method
    static ExecutionSummary* parse(std::byte* buffer) {
        return reinterpret_cast<ExecutionSummary*>(buffer);
    }

    // parse method const
    static const ExecutionSummary* parse(const std::byte* buffer) {
        return reinterpret_cast<const ExecutionSummary*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ExecutionSummary* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const ExecutionSummary*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
