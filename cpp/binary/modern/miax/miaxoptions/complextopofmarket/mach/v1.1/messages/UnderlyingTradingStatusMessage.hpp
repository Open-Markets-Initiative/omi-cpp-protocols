#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/EventReason.hpp"
#include "../types/SecondsPart.hpp"
#include "../types/ExpectedEventTimeNanoSecondsPart.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

#pragma pack(push, 1)

// This message format will be used to notify firms of changes to the trading status of all the options of an underlying
struct UnderlyingTradingStatusMessage {

    Nanoseconds nanoseconds;
    UnderlyingSymbol underlying_symbol;
    TradingStatus trading_status;
    EventReason event_reason;
    SecondsPart seconds_part;
    ExpectedEventTimeNanoSecondsPart expected_event_time_nano_seconds_part;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static UnderlyingTradingStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<UnderlyingTradingStatusMessage*>(buffer);
    }

    // parse method const
    static const UnderlyingTradingStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const UnderlyingTradingStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const UnderlyingTradingStatusMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const UnderlyingTradingStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
