#pragma once

#include "../types/OriginalSettlementType.hpp"
#include "../types/OriginalTradeThroughExemption.hpp"
#include "../types/OriginalExtendedHoursOrSoldCode.hpp"
#include "../types/OriginalSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

struct OriginalSaleConditionModifier {

    OriginalSettlementType original_settlement_type;
    OriginalTradeThroughExemption original_trade_through_exemption;
    OriginalExtendedHoursOrSoldCode original_extended_hours_or_sold_code;
    OriginalSpecialSaleCondition original_special_sale_condition;

    // parse method
    static OriginalSaleConditionModifier* parse(std::byte* buffer) {
        return reinterpret_cast<OriginalSaleConditionModifier*>(buffer);
    }

    // parse method const
    static const OriginalSaleConditionModifier* parse(const std::byte* buffer) {
        return reinterpret_cast<const OriginalSaleConditionModifier*>(buffer);
    }
};

#pragma pack(pop)
}
