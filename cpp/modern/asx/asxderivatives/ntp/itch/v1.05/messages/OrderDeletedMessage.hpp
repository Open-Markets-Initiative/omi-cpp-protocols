#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message is sent whenever an order in the book is cancelled by the owner, expired, cancelled by the exchange, purged or volume cancelled
struct OrderDeletedMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    Side side;
    OrderId order_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'D';

    // parse method
    static OrderDeletedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderDeletedMessage*>(buffer);
    }

    // parse method const
    static const OrderDeletedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderDeletedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderDeletedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderDeletedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
