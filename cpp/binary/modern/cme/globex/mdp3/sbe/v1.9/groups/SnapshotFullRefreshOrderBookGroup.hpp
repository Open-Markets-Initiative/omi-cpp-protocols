#pragma once

#include "../types/OrderId.hpp"
#include "../types/MdOrderPriority.hpp"
#include "../types/MdEntryPxEx.hpp"
#include "../types/MdDisplayQty.hpp"
#include "../types/MdEntryTypeBook.hpp"

namespace cme::mdp3::v9 {

#pragma pack(push, 1)

struct SnapshotFullRefreshOrderBookGroup {

    OrderId order_id;
    MdOrderPriority md_order_priority;
    MdEntryPxEx md_entry_px_ex;
    MdDisplayQty md_display_qty;
    MdEntryTypeBook md_entry_type_book;

    // parse method
    static SnapshotFullRefreshOrderBookGroup* parse(std::byte* buffer) {
        return reinterpret_cast<SnapshotFullRefreshOrderBookGroup*>(buffer);
    }

    // parse method const
    static const SnapshotFullRefreshOrderBookGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const SnapshotFullRefreshOrderBookGroup*>(buffer);
    }
};

#pragma pack(pop)
}
