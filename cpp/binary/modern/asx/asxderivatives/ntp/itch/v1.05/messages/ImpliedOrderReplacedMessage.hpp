#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookPriority.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// This message notifies the subscriber that an existing implied order is to be replaced when the implied price, volume or priority has changed due to a price or volume movement of “real” orders for a side of a single Tradeable Instrument Id
struct ImpliedOrderReplacedMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    Side side;
    OrderId order_id;
    OrderBookPriority order_book_priority;
    Quantity quantity;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'l';

    // parse method
    static ImpliedOrderReplacedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ImpliedOrderReplacedMessage*>(buffer);
    }

    // parse method const
    static const ImpliedOrderReplacedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ImpliedOrderReplacedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ImpliedOrderReplacedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ImpliedOrderReplacedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
