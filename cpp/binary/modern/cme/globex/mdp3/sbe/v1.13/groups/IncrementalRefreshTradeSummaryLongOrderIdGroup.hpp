#pragma once

#include "../types/OrderId.hpp"
#include "../types/LastQty.hpp"
#include "../types/Padding4.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshTradeSummaryLongOrderIdGroup {

    OrderId order_id;
    LastQty last_qty;
    Padding4 padding_4;

    // parse method
    static IncrementalRefreshTradeSummaryLongOrderIdGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshTradeSummaryLongOrderIdGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshTradeSummaryLongOrderIdGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshTradeSummaryLongOrderIdGroup*>(buffer);
    }
};

#pragma pack(pop)
}
