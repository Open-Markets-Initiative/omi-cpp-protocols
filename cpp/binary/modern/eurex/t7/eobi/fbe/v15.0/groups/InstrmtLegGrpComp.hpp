#pragma once

#include "../types/LegSymbol.hpp"
#include "../types/Pad4.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegPrice.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSecurityType.hpp"
#include "../types/LegSide.hpp"
#include "../types/RelatedPriceType.hpp"
#include "../types/TradingStyle.hpp"
#include "../types/RelatedPrice.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

#pragma pack(push, 1)

struct InstrmtLegGrpComp {

    LegSymbol leg_symbol;
    Pad4 pad4;
    LegSecurityId leg_security_id;
    LegPrice leg_price;
    LegRatioQty leg_ratio_qty;
    LegSecurityType leg_security_type;
    LegSide leg_side;
    RelatedPriceType related_price_type;
    TradingStyle trading_style;
    RelatedPrice related_price;

    // parse method
    static InstrmtLegGrpComp* parse(std::byte* buffer) {
        return reinterpret_cast<InstrmtLegGrpComp*>(buffer);
    }

    // parse method const
    static const InstrmtLegGrpComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrmtLegGrpComp*>(buffer);
    }
};

#pragma pack(pop)
}
