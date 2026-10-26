#pragma once

#include "../types/Nanoseconds.hpp"
#include "../types/OrderBookId.hpp"
#include "../types/AvailableBidQuantityAtEquilibriumPrice.hpp"
#include "../types/AvailableAskQuantityAtEquilibriumPrice.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/Reserved24.hpp"
#include "../structs/MessageHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

#pragma pack(push, 1)

// Provides changes in equilibrium price during auctions.
struct EquilibriumPriceUpdate {

    Nanoseconds nanoseconds;
    OrderBookId order_book_id;
    AvailableBidQuantityAtEquilibriumPrice available_bid_quantity_at_equilibrium_price;
    AvailableAskQuantityAtEquilibriumPrice available_ask_quantity_at_equilibrium_price;
    EquilibriumPrice equilibrium_price;
    Reserved24 reserved_24;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Z';

    // parse method
    static EquilibriumPriceUpdate* parse(std::byte* buffer) {
        return reinterpret_cast<EquilibriumPriceUpdate*>(buffer);
    }

    // parse method const
    static const EquilibriumPriceUpdate* parse(const std::byte* buffer) {
        return reinterpret_cast<const EquilibriumPriceUpdate*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const EquilibriumPriceUpdate* parse(const MessageHeader* header) {
        return reinterpret_cast<const EquilibriumPriceUpdate*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
