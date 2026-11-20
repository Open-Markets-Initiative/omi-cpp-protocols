// Cme.Globex.Mdp3.Sbe.v1.9: groups/SnapshotFullRefreshLegacyGroup.hpp
#pragma once

#include "../types/MdEntryPxOptional.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevelOptional.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../bitfields/SettlPriceType.hpp"
#include "../types/MdEntryType.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct SnapshotFullRefreshLegacyGroup {

    MdEntryPxOptional md_entry_px_optional;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    NumberOfOrdersOptional number_of_orders_optional;
    MdPriceLevelOptional md_price_level_optional;
    TradingReferenceDate trading_reference_date;
    OpenCloseSettlFlag open_close_settl_flag;
    SettlPriceType settl_price_type;
    MdEntryType md_entry_type;

    // parse method
    static SnapshotFullRefreshLegacyGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshLegacyGroup*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshLegacyGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshLegacyGroup*>(buffer);
    }
};

#pragma pack(pop)
}
