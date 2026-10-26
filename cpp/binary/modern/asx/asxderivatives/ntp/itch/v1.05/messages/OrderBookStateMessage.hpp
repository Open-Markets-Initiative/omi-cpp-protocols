#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/SessionState.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message indicates the current session state of a contract to the market
struct OrderBookStateMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    SessionState session_state;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'O';

    // parse method
    static OrderBookStateMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookStateMessage*>(buffer);
    }

    // parse method const
    static const OrderBookStateMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookStateMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderBookStateMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderBookStateMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
