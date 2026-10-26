#pragma once

#include "../types/Timestamp.hpp"
#include "../types/SecurityId.hpp"
#include "../types/TradeId.hpp"
#include "../types/OriginalQuantity.hpp"
#include "../types/OriginalPrice.hpp"
#include "../types/CorrectedQuantity.hpp"
#include "../types/CorrectedPrice.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

#pragma pack(push, 1)

// CorrectedTradeMessage
struct CorrectedTradeMessage {

    Timestamp timestamp;
    SecurityId security_id;
    TradeId trade_id;
    OriginalQuantity original_quantity;
    OriginalPrice original_price;
    CorrectedQuantity corrected_quantity;
    CorrectedPrice corrected_price;

    // parse method
    static CorrectedTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CorrectedTradeMessage*>(buffer);
    }

    // parse method const
    static const CorrectedTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CorrectedTradeMessage*>(buffer);
    }
};

#pragma pack(pop)
}
