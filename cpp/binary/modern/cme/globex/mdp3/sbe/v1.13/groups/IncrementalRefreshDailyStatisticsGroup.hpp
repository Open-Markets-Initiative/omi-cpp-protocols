#pragma once

#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/SecurityId.hpp"
#include "../types/RptSeq.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../types/MdUpdateAction.hpp"
#include "../types/MdEntryTypeDailyStatistics.hpp"
#include "../types/Padding7.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshDailyStatisticsGroup {

    MdEntryPxOptionalEx md_entry_px_optional_ex;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    SecurityId security_id;
    RptSeq rpt_seq;
    TradingReferenceDate trading_reference_date;
    SettlPriceType settl_price_type;
    MdUpdateAction md_update_action;
    MdEntryTypeDailyStatistics md_entry_type_daily_statistics;
    Padding7 padding_7;

    // parse method
    static IncrementalRefreshDailyStatisticsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshDailyStatisticsGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshDailyStatisticsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshDailyStatisticsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
