#pragma once

#include "../types/OrderToken.hpp"
#include "../types/Quantity.hpp"
#include "../messages/UnsequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// A Cancel Order Message is used to request that an order be canceled
struct CancelOrderMessage {

    OrderToken order_token;
    Quantity quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'X';

    // parse method
    static CancelOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CancelOrderMessage*>(buffer);
    }

    // parse method const
    static const CancelOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CancelOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CancelOrderMessage* parse(const UnsequencedDataPacket* header) {
        return reinterpret_cast<const CancelOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(UnsequencedDataPacket));
    }
};

#pragma pack(pop)
}
