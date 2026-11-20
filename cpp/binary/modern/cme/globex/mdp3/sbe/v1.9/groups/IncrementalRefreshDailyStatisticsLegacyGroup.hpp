// Cme.Globex.Mdp3.Sbe.v1.9: groups/IncrementalRefreshDailyStatisticsLegacyGroup.hpp
#pragma once

#include "../types/MdEntryPxOptional.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeDailyStatistics.hpp"
#include "../types/Padding7.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct IncrementalRefreshDailyStatisticsLegacyGroup {

    MdEntryPxOptional md_entry_px_optional;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    SecurityId security_id;
    RptSeq rpt_seq;
    TradingReferenceDate trading_reference_date;
    SettlPriceType settl_price_type;
    MdUpdateAction md_update_action;
    MdEntryTypeDailyStatistics md_entry_type_daily_statistics;
    Padding7 padding_7;

    // parse method
    static IncrementalRefreshDailyStatisticsLegacyGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshDailyStatisticsLegacyGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshDailyStatisticsLegacyGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshDailyStatisticsLegacyGroup*>(buffer);
    }
};

#pragma pack(pop)
}
