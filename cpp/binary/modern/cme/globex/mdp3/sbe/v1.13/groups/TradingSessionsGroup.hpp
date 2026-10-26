#pragma once

#include "../types/TradeDate.hpp"
#include "../types/SettlDate.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/SecurityAltId.hpp"

namespace cme::mdp3::v13 {

#pragma pack(push, 1)

struct TradingSessionsGroup {

    TradeDate trade_date;
    SettlDate settl_date;
    MaturityDate maturity_date;
    SecurityAltId security_alt_id;

    // parse method
    static TradingSessionsGroup* parse(std::byte* buffer) {
        return reinterpret_cast<TradingSessionsGroup*>(buffer);
    }

    // parse method const
    static const TradingSessionsGroup* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingSessionsGroup*>(buffer);
    }
};

#pragma pack(pop)
}
