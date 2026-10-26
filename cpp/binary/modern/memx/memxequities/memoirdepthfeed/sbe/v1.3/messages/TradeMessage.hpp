#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// TradeMessage
struct TradeMessage {

    Timestamp timestamp;
    SecurityId security_id;
    TradeId trade_id;
    Quantity quantity;
    Price price;

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
