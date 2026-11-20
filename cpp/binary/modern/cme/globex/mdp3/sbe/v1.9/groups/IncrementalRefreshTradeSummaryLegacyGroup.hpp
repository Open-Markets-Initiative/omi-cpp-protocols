// Cme.Globex.Mdp3.Sbe.v1.9: groups/IncrementalRefreshTradeSummaryLegacyGroup.hpp
#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/MdEntrySizeShort.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/AggressorSide.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdTradeEntryId.hpp"
#include "../types/Padding2.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct IncrementalRefreshTradeSummaryLegacyGroup {

    MdEntryPx md_entry_px;
    MdEntrySizeShort md_entry_size_short;
    SecurityId security_id;
    RptSeq rpt_seq;
    NumberOfOrdersOptional number_of_orders_optional;
    AggressorSide aggressor_side;
    MdUpdateAction md_update_action;
    MdTradeEntryId md_trade_entry_id;
    Padding2 padding_2;

    // parse method
    static IncrementalRefreshTradeSummaryLegacyGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshTradeSummaryLegacyGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshTradeSummaryLegacyGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshTradeSummaryLegacyGroup*>(buffer);
    }
};

#pragma pack(pop)
}
