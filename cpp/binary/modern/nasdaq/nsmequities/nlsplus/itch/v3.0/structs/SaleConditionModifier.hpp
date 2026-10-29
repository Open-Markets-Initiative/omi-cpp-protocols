#pragma once

#include "../types/SettlementType.hpp"
#include "../types/TradeThroughExemption.hpp"
#include "../types/ExtendedHoursOrSoldCode.hpp"
#include "../types/SpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

struct SaleConditionModifier {

    SettlementType settlement_type;
    TradeThroughExemption trade_through_exemption;
    ExtendedHoursOrSoldCode extended_hours_or_sold_code;
    SpecialSaleCondition special_sale_condition;

    // parse method
    static SaleConditionModifier* parse(std::byte* buffer) {
        return reinterpret_cast<SaleConditionModifier*>(buffer);
    }

    // parse method const
    static const SaleConditionModifier* parse(const std::byte* buffer) {
        return reinterpret_cast<const SaleConditionModifier*>(buffer);
    }
};

#pragma pack(pop)
}
