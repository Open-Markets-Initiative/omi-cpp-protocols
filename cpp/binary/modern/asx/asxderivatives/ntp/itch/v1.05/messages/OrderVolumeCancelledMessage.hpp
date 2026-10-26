#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/TradeableInstrumentId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderId.hpp"
#include "../types/Quantity.hpp"
#include "../structs/MessageHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

#pragma pack(push, 1)

// An Order Volume Cancelled message is sent when an order is modified as a result of partial cancellation of volume
struct OrderVolumeCancelledMessage {

    Nanoseconds nanoseconds;
    TradeDate trade_date;
    TradeableInstrumentId tradeable_instrument_id;
    Side side;
    OrderId order_id;
    Quantity quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static OrderVolumeCancelledMessage* parse(std::byte* buffer) {
        return reinterpret_cast<OrderVolumeCancelledMessage*>(buffer);
    }

    // parse method const
    static const OrderVolumeCancelledMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const OrderVolumeCancelledMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const OrderVolumeCancelledMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const OrderVolumeCancelledMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
