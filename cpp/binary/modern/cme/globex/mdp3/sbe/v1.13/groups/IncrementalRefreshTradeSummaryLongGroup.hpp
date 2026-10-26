#pragma once

#include "../types/MdEntryPxEx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrders.hpp"
#include "../types/MdTradeEntry.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/Padding6.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshTradeSummaryLongGroup {

    MdEntryPxEx md_entry_px_ex;
    MdEntrySize md_entry_size;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrders number_of_orders;
    MdTradeEntry md_trade_entry;
    AggressorSide aggressor_side;
    MdUpdateAction md_update_action;
    Padding6 padding_6;

    // parse method
    static IncrementalRefreshTradeSummaryLongGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshTradeSummaryLongGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshTradeSummaryLongGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshTradeSummaryLongGroup*>(buffer);
    }
};

#pragma pack(pop)
}
