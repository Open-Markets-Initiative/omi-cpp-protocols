#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/PairedQuantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/CrossLevel.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// Auction on demand order imbalance indicator
struct MoiiMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    PairedQuantity paired_quantity;
    OrderBook order_book;
    EquilibriumPrice equilibrium_price;
    CrossType cross_type;
    CrossLevel cross_level;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'J';

    // parse method
    static MoiiMessage* parse(std::byte* buffer) {
        return reinterpret_cast<MoiiMessage*>(buffer);
    }

    // parse method const
    static const MoiiMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const MoiiMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const MoiiMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const MoiiMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
