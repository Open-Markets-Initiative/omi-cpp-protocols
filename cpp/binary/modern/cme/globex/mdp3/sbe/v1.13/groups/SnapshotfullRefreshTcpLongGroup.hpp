#pragma once

#include "../types/MdEntryPxOptionalEx.hpp"
#include "../types/MdEntrySizeOptional.hpp"
#include "../types/NumberOfOrdersOptional.hpp"
#include "../types/MdPriceLevelUnsignedOptional.hpp"
#include "../types/OpenCloseSettlFlag.hpp"
#include "../types/MdEntryType.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct SnapshotfullRefreshTcpLongGroup {

    MdEntryPxOptionalEx md_entry_px_optional_ex;
    MdEntrySizeOptional md_entry_size_optional;
    NumberOfOrdersOptional number_of_orders_optional;
    MdPriceLevelUnsignedOptional md_price_level_unsigned_optional;
    OpenCloseSettlFlag open_close_settl_flag;
    MdEntryType md_entry_type;

    // parse method
    static SnapshotfullRefreshTcpLongGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotfullRefreshTcpLongGroup*>(buffer);
    }

    // parse method const
    static const SnapshotfullRefreshTcpLongGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotfullRefreshTcpLongGroup*>(buffer);
    }
};

#pragma pack(pop)
}
