#pragma once

#include <cstddef>
#include "../types/CorrectedSettlementType.hpp"
#include "../types/CorrectedTradeThroughExemption.hpp"
#include "../types/CorrectedExtendedHoursOrSoldCode.hpp"
#include "../types/CorrectedSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

#pragma pack(push, 1)

struct corrected_sale_condition_modifier {

    itch_nlsplus::corrected_settlement_type corrected_settlement_type;
    itch_nlsplus::corrected_trade_through_exemption corrected_trade_through_exemption;
    itch_nlsplus::corrected_extended_hours_or_sold_code corrected_extended_hours_or_sold_code;
    itch_nlsplus::corrected_special_sale_condition corrected_special_sale_condition;

    // parse method
    static corrected_sale_condition_modifier* parse(std::byte* buffer) {
        return reinterpret_cast<corrected_sale_condition_modifier*>(buffer);
    }

    // parse method const
    static const corrected_sale_condition_modifier* parse(const std::byte* buffer) {
        return reinterpret_cast<const corrected_sale_condition_modifier*>(buffer);
    }
};

// layout verification
static_assert(offsetof(corrected_sale_condition_modifier, corrected_settlement_type) == 0, "unexpected offset of corrected_sale_condition_modifier::corrected_settlement_type");
static_assert(offsetof(corrected_sale_condition_modifier, corrected_trade_through_exemption) == 1, "unexpected offset of corrected_sale_condition_modifier::corrected_trade_through_exemption");
static_assert(offsetof(corrected_sale_condition_modifier, corrected_extended_hours_or_sold_code) == 2, "unexpected offset of corrected_sale_condition_modifier::corrected_extended_hours_or_sold_code");
static_assert(offsetof(corrected_sale_condition_modifier, corrected_special_sale_condition) == 3, "unexpected offset of corrected_sale_condition_modifier::corrected_special_sale_condition");
static_assert(sizeof(corrected_sale_condition_modifier) == 4, "unexpected sizeof corrected_sale_condition_modifier");

#pragma pack(pop)
}
