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

// This message is a similar format to the Order Added message, except the nature of this order is it has an implied price, implied volume and a priority that is derived from two or more “real” orders deriving the implied price
struct ImpliedOrderAddedMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    Side side;
    OrderId order_id;
    OrderBookPriority order_book_priority;
    Quantity quantity;
    Price price;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'j';

    // parse method
    static ImpliedOrderAddedMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ImpliedOrderAddedMessage*>(buffer);
    }

    // parse method const
    static const ImpliedOrderAddedMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ImpliedOrderAddedMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ImpliedOrderAddedMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const ImpliedOrderAddedMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
