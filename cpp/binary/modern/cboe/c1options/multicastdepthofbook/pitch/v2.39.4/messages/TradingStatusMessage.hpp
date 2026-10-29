#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/ExpandedSymbol.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/RegShoAction.hpp"
#include "../types/Reserved1.hpp"
#include "../types/SecondReserved1.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

#pragma pack(push, 1)

// The Trading Status message is used to indicate the current trading status of a security. A Trading Status message will be sent whenever a security’s trading status changes.
struct TradingStatusMessage {

    TimeOffset time_offset;
    ExpandedSymbol expanded_symbol;
    TradingStatus trading_status;
    RegShoAction reg_sho_action;
    Reserved1 reserved_1;
    SecondReserved1 second_reserved_1;

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
