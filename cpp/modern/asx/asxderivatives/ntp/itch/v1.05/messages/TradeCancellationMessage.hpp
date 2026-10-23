#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/TradeId.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message is sent whenever a trade is cancelled by ASX
struct TradeCancellationMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    TradeId trade_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'B';

    // parse method
    static TradeCancellationMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeCancellationMessage*>(buffer);
    }

    // parse method const
    static const TradeCancellationMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeCancellationMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeCancellationMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeCancellationMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
