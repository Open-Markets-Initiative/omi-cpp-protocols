#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySize.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrders.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/Padding6.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

struct IncrementalRefreshTradeSummaryGroup {

    MdEntryPx md_entry_px;
    MdEntrySize md_entry_size;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrders number_of_orders;
    AggressorSide aggressor_side;
    MdUpdateAction md_update_action;
    Padding6 padding_6;

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
