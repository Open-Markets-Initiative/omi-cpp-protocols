#pragma once

#include "../types/TradingSessionId.hpp"
#include "../types/TradingSessionSubId.hpp"
#include "../types/TradSesStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/Pad3.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct ProductStateChange {

    TradingSessionId trading_session_id;
    TradingSessionSubId trading_session_sub_id;
    TradSesStatus trad_ses_status;
    MarketCondition market_condition;
    FastMarketIndicator fast_market_indicator;
    Pad3 pad3;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13300;

    // parse method
    static ProductStateChange* parse(std::byte* buffer) {
        return reinterpret_cast<ProductStateChange*>(buffer);
    }

    // parse method const
    static const ProductStateChange* parse(const std::byte* buffer) {
        return reinterpret_cast<const ProductStateChange*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ProductStateChange* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const ProductStateChange*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
