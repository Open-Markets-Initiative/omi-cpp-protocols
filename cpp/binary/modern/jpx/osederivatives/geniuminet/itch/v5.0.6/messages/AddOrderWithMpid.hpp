#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/Side.hpp"
#include "../types/OrderBookPosition.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../bitfields/OrderAttributes.hpp"
#include "../types/LotType.hpp"
#include "../types/ParticipantId.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// New order accepted (attributed).
struct AddOrderWithMpid {

    Nanoseconds nanoseconds;
    OrderId order_id;
    OrderBookId order_book_id;
    Side side;
    OrderBookPosition order_book_position;
    Quantity quantity;
    Price price;
    OrderAttributes order_attributes;
    LotType lot_type;
    ParticipantId participant_id;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'F';

    // parse method
    static AddOrderWithMpid* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderWithMpid*>(buffer);
    }

    // parse method const
    static const AddOrderWithMpid* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderWithMpid*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderWithMpid* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderWithMpid*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
