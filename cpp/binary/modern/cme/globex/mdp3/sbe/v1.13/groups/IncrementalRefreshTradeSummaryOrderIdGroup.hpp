#pragma once

#include "../types/OrderId.hpp"
#include "../types/LastQty.hpp"
#include "../types/Padding4.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct IncrementalRefreshTradeSummaryOrderIdGroup {

    OrderId order_id;
    LastQty last_qty;
    Padding4 padding_4;

    // parse method
    static IncrementalRefreshTradeSummaryOrderIdGroup* parse(std::byte* buffer) {
        return reinterpret_cast<IncrementalRefreshTradeSummaryOrderIdGroup*>(buffer);
    }

    // parse method const
    static const IncrementalRefreshTradeSummaryOrderIdGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const IncrementalRefreshTradeSummaryOrderIdGroup*>(buffer);
    }
};

#pragma pack(pop)
}
