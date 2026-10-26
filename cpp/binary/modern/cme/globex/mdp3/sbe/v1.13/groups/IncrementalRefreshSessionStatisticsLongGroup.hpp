#pragma once

#include "../types/MdEntryPxEx.hpp"
#include "../types/MdEntrySizeOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeStatistics.hpp"
#include "../types/Padding5.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshSessionStatisticsLongGroup {

    MdEntryPxEx md_entry_px_ex;
    MdEntrySizeOptional md_entry_size_optional;
    SecurityId security_id;
    RptSeq rpt_seq;
    OpenCloseSettlFlag open_close_settl_flag;
    MdUpdateAction md_update_action;
    MdEntryTypeStatistics md_entry_type_statistics;
    Padding5 padding_5;

    // parse method
    static IncrementalRefreshSessionStatisticsLongGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshSessionStatisticsLongGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshSessionStatisticsLongGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshSessionStatisticsLongGroup*>(buffer);
    }
};

#pragma pack(pop)
}
