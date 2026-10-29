#pragma once

#include "../types/ExistingOrderToken.hpp"
#include "../types/ReplacementOrderToken.hpp"
#include "../types/Quantity.hpp"
#include "../types/Price.hpp"
#include "../types/TimeInForce.hpp"
#include "../types/Display.hpp"
#include "../types/MinimumQuantity.hpp"
#include "../messages/UnsequencedDataPacket.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

#pragma pack(push, 1)

// A Replace Order Message is used to modify an existing order
struct ReplaceOrderMessage {

    ExistingOrderToken existing_order_token;
    ReplacementOrderToken replacement_order_token;
    Quantity quantity;
    Price price;
    TimeInForce time_in_force;
    Display display;
    MinimumQuantity minimum_quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'U';

    // parse method
    static ReplaceOrderMessage* parse(std::byte* buffer) {
        return reinterpret_cast<ReplaceOrderMessage*>(buffer);
    }

    // parse method const
    static const ReplaceOrderMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const ReplaceOrderMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const ReplaceOrderMessage* parse(const UnsequencedDataPacket* header) {
        return reinterpret_cast<const ReplaceOrderMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(UnsequencedDataPacket));
    }
};

#pragma pack(pop)
}
