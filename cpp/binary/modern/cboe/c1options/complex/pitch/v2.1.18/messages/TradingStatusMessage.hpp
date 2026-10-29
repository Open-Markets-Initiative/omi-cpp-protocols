#pragma once

#include "../types/TimeOffset.hpp"
#include "../types/ComplexSymbolId.hpp"
#include "../types/Unused.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/Reserved1.hpp"
#include "../types/GthTradingStatus.hpp"
#include "../types/Padding.hpp"
#include "../structs/MessageHeader.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

#pragma pack(push, 1)

// The Trading Status message is used to indicate the current trading status of a complex instrument.
struct TradingStatusMessage {

    TimeOffset time_offset;
    ComplexSymbolId complex_symbol_id;
    Unused unused;
    TradingStatus trading_status;
    Reserved1 reserved_1;
    GthTradingStatus gth_trading_status;
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
