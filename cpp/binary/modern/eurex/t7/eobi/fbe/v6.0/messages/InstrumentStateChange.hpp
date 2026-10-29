#pragma once

#include "../types/SecurityId.hpp"
#include "../types/SecurityStatus.hpp"
#include "../types/SecurityTradingStatus.hpp"
#include "../types/MarketCondition.hpp"
#include "../types/FastMarketIndicator.hpp"
#include "../types/SecurityTradingEvent.hpp"
#include "../types/Pad3.hpp"
#include "../types/TransactTime.hpp"
#include "../structs/MessageHeaderComp.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

#pragma pack(push, 1)

// 
struct InstrumentStateChange {

    SecurityId security_id;
    SecurityStatus security_status;
    SecurityTradingStatus security_trading_status;
    MarketCondition market_condition;
    FastMarketIndicator fast_market_indicator;
    SecurityTradingEvent security_trading_event;
    Pad3 pad3;
    TransactTime transact_time;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint16_t message_type = 13301;

    // parse method
    static InstrumentStateChange* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentStateChange*>(buffer);
    }

    // parse method const
    static const InstrumentStateChange* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentStateChange*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentStateChange* parse(const MessageHeaderComp* header) {
        return reinterpret_cast<const InstrumentStateChange*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeaderComp));
    }
};

#pragma pack(pop)
}
