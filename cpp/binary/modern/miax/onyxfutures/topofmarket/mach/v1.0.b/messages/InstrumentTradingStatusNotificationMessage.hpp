#pragma once

#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/MarketState.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

#pragma pack(push, 1)

// Used to notify firms of changes to the trading status of a particular Simple or Complex instrument
struct InstrumentTradingStatusNotificationMessage {

    Timestamp timestamp;
    InstrumentId instrument_id;
    TradingStatus trading_status;
    MarketState market_state;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 4;

    // parse method
    static InstrumentTradingStatusNotificationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<InstrumentTradingStatusNotificationMessage*>(buffer);
    }

    // parse method const
    static const InstrumentTradingStatusNotificationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const InstrumentTradingStatusNotificationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const InstrumentTradingStatusNotificationMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const InstrumentTradingStatusNotificationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
