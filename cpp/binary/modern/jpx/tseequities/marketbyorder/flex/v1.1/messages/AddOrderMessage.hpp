#pragma once

#include "../types/TimeMicroseconds.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../types/OrderCondition.hpp"
#include "../types/ModificationFlag.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

#pragma pack(push, 1)

// Provides information about book registration. Delivered when a new order or modification order is registered.
struct AddOrderMessage {

    TimeMicroseconds time_microseconds;
    OrderId order_id;
    Side side;
    Quantity quantity;
    Price price;
    OrderCondition order_condition;
    ModificationFlag modification_flag;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'A';

    // parse method
    static AddOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const AddOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
