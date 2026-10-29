#pragma once

#include <cstddef>
#include "../types/SettlementType.hpp"
#include "../types/TradeThroughExemptReason.hpp"
#include "../types/ExtendedHoursOrSequenceType.hpp"
#include "../types/SroTradeDetail.hpp"

namespace siac::cts::output::cta::v2_10 {

namespace cta_output = ::siac::cts::output::cta::v2_10;

#pragma pack(push, 1)

struct sale_conditions {

    cta_output::settlement_type settlement_type;
    cta_output::trade_through_exempt_reason trade_through_exempt_reason;
    cta_output::extended_hours_or_sequence_type extended_hours_or_sequence_type;
    cta_output::sro_trade_detail sro_trade_detail;

    // parse method
    static sale_conditions* parse(std::byte* buffer) {
        return reinterpret_cast<sale_conditions*>(buffer);
    }

    // parse method const
    static const sale_conditions* parse(const std::byte* buffer) {
        return reinterpret_cast<const sale_conditions*>(buffer);
    }
};

// layout verification
static_assert(offsetof(sale_conditions, settlement_type) == 0, "unexpected offset of sale_conditions::settlement_type");
static_assert(offsetof(sale_conditions, trade_through_exempt_reason) == 1, "unexpected offset of sale_conditions::trade_through_exempt_reason");
static_assert(offsetof(sale_conditions, extended_hours_or_sequence_type) == 2, "unexpected offset of sale_conditions::extended_hours_or_sequence_type");
static_assert(offsetof(sale_conditions, sro_trade_detail) == 3, "unexpected offset of sale_conditions::sro_trade_detail");
static_assert(sizeof(sale_conditions) == 4, "unexpected sizeof sale_conditions");

#pragma pack(pop)
}
