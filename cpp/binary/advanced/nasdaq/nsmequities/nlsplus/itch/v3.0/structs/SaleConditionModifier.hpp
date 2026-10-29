#pragma once

#include <cstddef>
#include "../types/SettlementType.hpp"
#include "../types/TradeThroughExemption.hpp"
#include "../types/ExtendedHoursOrSoldCode.hpp"
#include "../types/SpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

struct sale_condition_modifier {

    itch_nlsplus::settlement_type settlement_type;
    itch_nlsplus::trade_through_exemption trade_through_exemption;
    itch_nlsplus::extended_hours_or_sold_code extended_hours_or_sold_code;
    itch_nlsplus::special_sale_condition special_sale_condition;

    // parse method
    static sale_condition_modifier* parse(std::byte* buffer) {
        return reinterpret_cast<sale_condition_modifier*>(buffer);
    }

    // parse method const
    static const sale_condition_modifier* parse(const std::byte* buffer) {
        return reinterpret_cast<const sale_condition_modifier*>(buffer);
    }
};

// layout verification
static_assert(offsetof(sale_condition_modifier, settlement_type) == 0, "unexpected offset of sale_condition_modifier::settlement_type");
static_assert(offsetof(sale_condition_modifier, trade_through_exemption) == 1, "unexpected offset of sale_condition_modifier::trade_through_exemption");
static_assert(offsetof(sale_condition_modifier, extended_hours_or_sold_code) == 2, "unexpected offset of sale_condition_modifier::extended_hours_or_sold_code");
static_assert(offsetof(sale_condition_modifier, special_sale_condition) == 3, "unexpected offset of sale_condition_modifier::special_sale_condition");
static_assert(sizeof(sale_condition_modifier) == 4, "unexpected sizeof sale_condition_modifier");

#pragma pack(pop)
}
