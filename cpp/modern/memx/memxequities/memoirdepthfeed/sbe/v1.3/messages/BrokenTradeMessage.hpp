#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TradeId.hpp"
#include "../types/OriginalQuantity.hpp"
#include "../types/OriginalPrice.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// BrokenTradeMessage
struct BrokenTradeMessage {

    Timestamp timestamp;
    SecurityId security_id;
    TradeId trade_id;
    OriginalQuantity original_quantity;
    OriginalPrice original_price;

    // parse method
    static BrokenTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<BrokenTradeMessage*>(buffer);
    }

    // parse method const
    static const BrokenTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const BrokenTradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
