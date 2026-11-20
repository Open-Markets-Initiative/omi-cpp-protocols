// Cme.Globex.Mdp3.Sbe.v1.9: groups/SnapshotFullRefreshOrderBookLegacyGroup.hpp
#pragma once

#include "../types/OrderId.hpp"
#include "../types/MdOrderPriority.hpp"
#include "../types/MdEntryPx.hpp"
#include "../types/MdDisplayQty.hpp"
#include "../types/MdEntryTypeBook.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct SnapshotFullRefreshOrderBookLegacyGroup {

    OrderId order_id;
    MdOrderPriority md_order_priority;
    MdEntryPx md_entry_px;
    MdDisplayQty md_display_qty;
    MdEntryTypeBook md_entry_type_book;

    // parse method
    static SnapshotFullRefreshOrderBookLegacyGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshOrderBookLegacyGroup*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshOrderBookLegacyGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshOrderBookLegacyGroup*>(buffer);
    }
};

#pragma pack(pop)
}
