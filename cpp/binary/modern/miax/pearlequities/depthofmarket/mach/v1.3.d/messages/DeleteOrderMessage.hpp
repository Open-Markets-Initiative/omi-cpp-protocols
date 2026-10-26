#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/SymbolId.hpp"
#include "../types/OrderId.hpp"
#include "../structs/ApplicationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

#pragma pack(push, 1)

// This message format is used to indicate that a displayed order has been removed from the MIAX Pearl Equities book.
struct DeleteOrderMessage {

    Nanoseconds nanoseconds;
    SymbolId symbol_id;
    OrderId order_id;

    // the type code that selects this message in the dispatch switch
    static constexpr std::uint8_t message_type = 23;

    // parse method
    static DeleteOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<DeleteOrderMessage*>(buffer);
    }

    // parse method const
    static const DeleteOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const DeleteOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const DeleteOrderMessage* parse(const ApplicationMessage* header) {
        return reinterpret_cast<const DeleteOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(ApplicationMessage));
    }
};

#pragma pack(pop)
}
