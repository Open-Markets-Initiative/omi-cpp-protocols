#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/SymbolLong.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/RegShoAction.hpp"
#include "../types/Padding.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29 {

#pragma pack(push, 1)

// The Trading Status message is used to indicate the current trading status of a complex instrument.
struct TradingStatusMessage {

    TimeOffset time_offset;
    SymbolLong symbol_long;
    TradingStatus trading_status;
    RegShoAction reg_sho_action;
    Padding padding;

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
