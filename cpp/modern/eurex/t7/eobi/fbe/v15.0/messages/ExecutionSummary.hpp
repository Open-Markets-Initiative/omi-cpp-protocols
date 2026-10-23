#pragma once

#include "../types/SecurityId.hpp"
#include "../types/RequestTime.hpp"
#include "../types/ExecId.hpp"
#include "../types/LastQty.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/Pad1.hpp"
#include "../types/TradeCondition.hpp"
#include "../types/TradingHhiIndicator.hpp"
#include "../types/Pad3.hpp"
#include "../types/LastPx.hpp"
#include "../structs/RemainingOrderDetailsComp.hpp"
#include "../types/RestingHiddenQty.hpp"
#include "../types/RestingCxlQty.hpp"
#include "../types/AggressorTime.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

// 
struct ExecutionSummary {

    SecurityId security_id;
    RequestTime request_time;
    ExecId exec_id;
    LastQty last_qty;
    AggressorSide aggressor_side;
    Pad1 pad1;
    TradeCondition trade_condition;
    TradingHhiIndicator trading_hhi_indicator;
    Pad3 pad3;
    LastPx last_px;
    RemainingOrderDetailsComp remaining_order_details_comp;
    RestingHiddenQty resting_hidden_qty;
    RestingCxlQty resting_cxl_qty;
    AggressorTime aggressor_time;

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
