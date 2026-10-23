#pragma once

#include "../types/SecurityId.hpp"
#include "../types/HighPx.hpp"
#include "../types/LowPx.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/SoldOutIndicator.hpp"
#include "../types/TesSecurityStatus.hpp"
#include "../types/Pad2.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

#pragma pack(push, 1)

struct SecMassStatGrpComp {

    SecurityId security_id;
    HighPx high_px;
    LowPx low_px;
    SecurityStatus security_status;
    SecurityTradingStatus security_trading_status;
    MarketCondition market_condition;
    SecurityTradingEvent security_trading_event;
    SoldOutIndicator sold_out_indicator;
    TesSecurityStatus tes_security_status;
    Pad2 pad2;

    // parse method
    static SecMassStatGrpComp* parse(std::byte* buffer) {
        return reinterpret_cast<SecMassStatGrpComp*>(buffer);
    }

    // parse method const
    static const SecMassStatGrpComp* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecMassStatGrpComp*>(buffer);
    }
};

#pragma pack(pop)
}
