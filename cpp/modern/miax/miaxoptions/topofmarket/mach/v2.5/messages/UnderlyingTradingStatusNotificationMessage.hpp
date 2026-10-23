#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/EventReason.hpp"
#include "../types/ExpectedEventTimeSecondsPart.hpp"
#include "../types/ExpectedEventTimeNanoSecondsPart.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

#pragma pack(push, 1)

// This message format will be used to notify firms of changes to the trading status of all the options of an underlying.
struct UnderlyingTradingStatusNotificationMessage {

    Nanoseconds nanoseconds;
    UnderlyingSymbol underlying_symbol;
    TradingStatus trading_status;
    EventReason event_reason;
    ExpectedEventTimeSecondsPart expected_event_time_seconds_part;
    ExpectedEventTimeNanoSecondsPart expected_event_time_nano_seconds_part;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static UnderlyingTradingStatusNotificationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingTradingStatusNotificationMessage*>(buffer);
    }

    // parse method const
    static const UnderlyingTradingStatusNotificationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingTradingStatusNotificationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const UnderlyingTradingStatusNotificationMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const UnderlyingTradingStatusNotificationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
