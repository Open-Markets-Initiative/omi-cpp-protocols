#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/MarketState.hpp"
#include "../types/ShortSaleRestriction.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This message is used to notify firms of changes to the trading status of a particular security.
struct SecurityTradingStatusNotificationMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;
    TradingStatus trading_status;
    MarketState market_state;
    ShortSaleRestriction short_sale_restriction;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 4;

    // parse method
    static SecurityTradingStatusNotificationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<SecurityTradingStatusNotificationMessage*>(buffer);
    }

    // parse method const
    static const SecurityTradingStatusNotificationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const SecurityTradingStatusNotificationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const SecurityTradingStatusNotificationMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const SecurityTradingStatusNotificationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
