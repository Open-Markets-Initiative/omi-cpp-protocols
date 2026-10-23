#pragma once

#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeShortOptional.hpp"
#include "../types/TradeableSize.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevelOptional.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/MdEntryType.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../bitfields/SettlPriceType.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct SnapshotFullRefreshTcpGroup {

    MdEntryPxOptionalEx md_entry_px_optional_ex;
    MdEntrySizeShortOptional md_entry_size_short_optional;
    TradeableSize tradeable_size;
    NumberOfOrdersOptional number_of_orders_optional;
    MdPriceLevelOptional md_price_level_optional;
    OpenCloseSettlFlag open_close_settl_flag;
    MdEntryType md_entry_type;
    TradingReferenceDate trading_reference_date;
    SettlPriceType settl_price_type;

    // parse method
    static SnapshotFullRefreshTcpGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshTcpGroup*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshTcpGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshTcpGroup*>(buffer);
    }
};

#pragma pack(pop)
}
