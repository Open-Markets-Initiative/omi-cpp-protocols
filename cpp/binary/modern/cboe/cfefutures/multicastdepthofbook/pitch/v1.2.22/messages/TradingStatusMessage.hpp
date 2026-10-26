#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/Reserved2.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/Reserved3.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

#pragma pack(push, 1)

// The Trading Status message is used to indicate the current trading status of a Futures contract.
struct TradingStatusMessage {

    TimeOffset time_offset;
    Symbol symbol;
    Reserved2 reserved_2;
    TradingStatus trading_status;
    Reserved3 reserved_3;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 0x31;

    // parse method
    static TradingStatusMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradingStatusMessage*>(buffer);
    }

    // parse method const
    static const TradingStatusMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradingStatusMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradingStatusMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradingStatusMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
