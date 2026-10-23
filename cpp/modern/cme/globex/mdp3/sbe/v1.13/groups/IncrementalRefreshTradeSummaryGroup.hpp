#pragma once

#include "../types/MdEntryPxEx.hpp"
#include "../types/MdEntrySizeShort.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrders.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdTradeEntryOptional.hpp"
#include "../types/Padding2.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshTradeSummaryGroup {

    MdEntryPxEx md_entry_px_ex;
    MdEntrySizeShort md_entry_size_short;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrders number_of_orders;
    AggressorSide aggressor_side;
    MdUpdateAction md_update_action;
    MdTradeEntryOptional md_trade_entry_optional;
    Padding2 padding_2;

    // parse method
    static IncrementalRefreshTradeSummaryGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshTradeSummaryGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshTradeSummaryGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshTradeSummaryGroup*>(buffer);
    }
};

#pragma pack(pop)
}
