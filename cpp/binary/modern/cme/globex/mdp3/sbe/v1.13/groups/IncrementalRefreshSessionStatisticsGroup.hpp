#pragma once

#include "../types/MdEntryPxEx.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeStatistics.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/Padding1.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshSessionStatisticsGroup {

    MdEntryPxEx md_entry_px_ex;
    SecurityId security_id;
    RptSeq rpt_seq;
    OpenCloseSettlFlag open_close_settl_flag;
    MdUpdateAction md_update_action;
    MdEntryTypeStatistics md_entry_type_statistics;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    Padding1 padding_1;

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
