#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrders.hpp"
#include "../types/TradeId.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/Padding2.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

struct IncrementalRefreshTradeGroup {

    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrders number_of_orders;
    TradeId trade_id;
    AggressorSide aggressor_side;
    MdUpdateAction md_update_action;
    Padding2 padding_2;

    // parse method
    static IncrementalRefreshTradeGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshTradeGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshTradeGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshTradeGroup*>(buffer);
    }
};

#pragma pack(pop)
}
