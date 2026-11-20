// Cme.Globex.Mdp3.Sbe.v1.9: groups/IncrementalRefreshSessionStatisticsLegacyGroup.hpp
#pragma once

#include "../types/MdEntryPx.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeStatistics.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/Padding1.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct IncrementalRefreshSessionStatisticsLegacyGroup {

    MdEntryPx md_entry_px;
    SecurityId security_id;
    RptSeq rpt_seq;
    OpenCloseSettlFlag open_close_settl_flag;
    MdUpdateAction md_update_action;
    MdEntryTypeStatistics md_entry_type_statistics;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    Padding1 padding_1;

    // parse method
    static IncrementalRefreshSessionStatisticsLegacyGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshSessionStatisticsLegacyGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshSessionStatisticsLegacyGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshSessionStatisticsLegacyGroup*>(buffer);
    }
};

#pragma pack(pop)
}
