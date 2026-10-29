#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeStatistics.hpp"
#include "../types/Padding5.hpp"

namespace cme::mdp3::v5 {

#pragma pack(push, 1)

struct IncrementalRefreshSessionStatisticsGroup {

    MdEntryPx md_entry_px;
    SecurityId security_id;
    RptSeq rpt_seq;
    OpenCloseSettlFlag open_close_settl_flag;
    MdUpdateAction md_update_action;
    MdEntryTypeStatistics md_entry_type_statistics;
    Padding5 padding_5;

    // parse method
    static IncrementalRefreshSessionStatisticsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshSessionStatisticsGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshSessionStatisticsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshSessionStatisticsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
