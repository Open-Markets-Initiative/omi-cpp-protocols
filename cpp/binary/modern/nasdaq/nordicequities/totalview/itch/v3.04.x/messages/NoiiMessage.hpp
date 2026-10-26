#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/PairedQuantity.hpp"
#include "../types/ImbalanceQuantity.hpp"
#include "../types/ImbalanceDirection.hpp"
#include "../types/OrderBook.hpp"
#include "../types/EquilibriumPrice.hpp"
#include "../types/CrossType.hpp"
#include "../types/BestBidPrice.hpp"
#include "../types/BestBidQuantity.hpp"
#include "../types/BestAskPrice.hpp"
#include "../types/BestAskQuantity.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// Net order imbalance indicator disseminated during a cross auction
struct NoiiMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    PairedQuantity paired_quantity;
    ImbalanceQuantity imbalance_quantity;
    ImbalanceDirection imbalance_direction;
    OrderBook order_book;
    EquilibriumPrice equilibrium_price;
    CrossType cross_type;
    BestBidPrice best_bid_price;
    BestBidQuantity best_bid_quantity;
    BestAskPrice best_ask_price;
    BestAskQuantity best_ask_quantity;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'I';

    // parse method
    static NoiiMessage* parse(std::byte* buffer) {
        return reinterpret_cast<NoiiMessage*>(buffer);
    }

    // parse method const
    static const NoiiMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const NoiiMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const NoiiMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const NoiiMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
