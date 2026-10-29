#pragma once

#include <cstddef>
#include "../types/OriginalSettlementType.hpp"
#include "../types/OriginalTradeThroughExemption.hpp"
#include "../types/OriginalExtendedHoursOrSoldCode.hpp"
#include "../types/OriginalSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

struct original_sale_condition_modifier {

    itch_nlsplus::original_settlement_type original_settlement_type;
    itch_nlsplus::original_trade_through_exemption original_trade_through_exemption;
    itch_nlsplus::original_extended_hours_or_sold_code original_extended_hours_or_sold_code;
    itch_nlsplus::original_special_sale_condition original_special_sale_condition;

    // parse method
    static original_sale_condition_modifier* parse(std::byte* buffer) {
        return reinterpret_cast<original_sale_condition_modifier*>(buffer);
    }

    // parse method const
    static const original_sale_condition_modifier* parse(const std::byte* buffer) {
        return reinterpret_cast<const original_sale_condition_modifier*>(buffer);
    }
};

// layout verification
static_assert(offsetof(original_sale_condition_modifier, original_settlement_type) == 0, "unexpected offset of original_sale_condition_modifier::original_settlement_type");
static_assert(offsetof(original_sale_condition_modifier, original_trade_through_exemption) == 1, "unexpected offset of original_sale_condition_modifier::original_trade_through_exemption");
static_assert(offsetof(original_sale_condition_modifier, original_extended_hours_or_sold_code) == 2, "unexpected offset of original_sale_condition_modifier::original_extended_hours_or_sold_code");
static_assert(offsetof(original_sale_condition_modifier, original_special_sale_condition) == 3, "unexpected offset of original_sale_condition_modifier::original_special_sale_condition");
static_assert(sizeof(original_sale_condition_modifier) == 4, "unexpected sizeof original_sale_condition_modifier");

#pragma pack(pop)
}
