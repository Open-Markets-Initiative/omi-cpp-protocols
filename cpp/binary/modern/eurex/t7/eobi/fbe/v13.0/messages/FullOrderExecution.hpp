#pragma once

#include "../types/Side.hpp"
#include "../types/OrdType.hpp"
#include "../types/AlgorithmicTradeIndicator.hpp"
#include "../types/HhiIndicator.hpp"
#include "../types/TrdMatchId.hpp"
#include "../types/Price.hpp"
#include "../types/TrdRegTsTimePriority.hpp"
#include "../types/SecurityId.hpp"
#include "../types/LastQty.hpp"
#include "../types/LastPx.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

// 
struct FullOrderExecution {

    Side side;
    OrdType ord_type;
    AlgorithmicTradeIndicator algorithmic_trade_indicator;
    HhiIndicator hhi_indicator;
    TrdMatchId trd_match_id;
    Price price;
    TrdRegTsTimePriority trd_reg_ts_time_priority;
    SecurityId security_id;
    LastQty last_qty;
    LastPx last_px;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13104;

    // parse method
    static FullOrderExecution* parse(std::byte* buffer) {
        return reinterpret_cast<FullOrderExecution*>(buffer);
    }

    // parse method const
    static const FullOrderExecution* parse(const std::byte* buffer) {
        return reinterpret_cast<const FullOrderExecution*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const FullOrderExecution* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const FullOrderExecution*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
