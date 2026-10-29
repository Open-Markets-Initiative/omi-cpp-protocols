#pragma once

#include "../types/CorrectedSettlementType.hpp"
#include "../types/CorrectedTradeThroughExemption.hpp"
#include "../types/CorrectedExtendedHoursOrSoldCode.hpp"
#include "../types/CorrectedSpecialSaleCondition.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

#pragma pack(push, 1)

struct CorrectedSaleConditionModifier {

    CorrectedSettlementType corrected_settlement_type;
    CorrectedTradeThroughExemption corrected_trade_through_exemption;
    CorrectedExtendedHoursOrSoldCode corrected_extended_hours_or_sold_code;
    CorrectedSpecialSaleCondition corrected_special_sale_condition;

    // parse method
    static CorrectedSaleConditionModifier* parse(std::byte* buffer) {
        return reinterpret_cast<CorrectedSaleConditionModifier*>(buffer);
    }

    // parse method const
    static const CorrectedSaleConditionModifier* parse(const std::byte* buffer) {
        return reinterpret_cast<const CorrectedSaleConditionModifier*>(buffer);
    }
};

#pragma pack(pop)
}
