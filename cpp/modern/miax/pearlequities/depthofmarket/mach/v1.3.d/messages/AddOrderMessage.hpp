#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../types/OrderSide.hpp"
#include "../types/Price.hpp"
#include "../types/Size.hpp"
#include "../types/AttributableId.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This is the message format that will be used when a displayed order is received and added to MIAX Pearl Equities book. It includes an Order ID that is unique to the order across the exchange and across trading days.
struct AddOrderMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;
    OrderId order_id;
    OrderSide order_side;
    Price price;
    Size size;
    AttributableId attributable_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 20;

    // parse method
    static AddOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<AddOrderMessage*>(buffer);
    }

    // parse method const
    static const AddOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const AddOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const AddOrderMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const AddOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
