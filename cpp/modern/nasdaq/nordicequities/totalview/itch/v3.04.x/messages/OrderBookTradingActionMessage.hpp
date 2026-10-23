#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderBook.hpp"
#include "../types/SymbolState.hpp"
#include "../types/Extension.hpp"
#include "../types/Reason.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// Indicates the current trading status of a security
struct OrderBookTradingActionMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderBook order_book;
    SymbolState symbol_state;
    Extension extension;
    Reason reason;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'H';

    // parse method
    static OrderBookTradingActionMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderBookTradingActionMessage*>(buffer);
    }

    // parse method const
    static const OrderBookTradingActionMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderBookTradingActionMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderBookTradingActionMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderBookTradingActionMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
