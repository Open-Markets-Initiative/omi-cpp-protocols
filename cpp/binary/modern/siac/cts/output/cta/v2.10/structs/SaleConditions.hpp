#pragma once

#include "../types/SettlementType.hpp"
#include "../types/TradeThroughExemptReason.hpp"
#include "../types/ExtendedHoursOrSequenceType.hpp"
#include "../types/SroTradeDetail.hpp"

namespace siac::cts::output::cta::v2_10 {

#pragma pack(push, 1)

struct SaleConditions {

    SettlementType settlement_type;
    TradeThroughExemptReason trade_through_exempt_reason;
    ExtendedHoursOrSequenceType extended_hours_or_sequence_type;
    SroTradeDetail sro_trade_detail;

    // parse method
    static SaleConditions* parse(std::byte* buffer) {
        return reinterpret_cast<SaleConditions*>(buffer);
    }

    // parse method const
    static const SaleConditions* parse(const std::byte* buffer) {
        return reinterpret_cast<const SaleConditions*>(buffer);
    }
};

#pragma pack(pop)
}
