#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/CrossPrice.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/CrossType.hpp"
#include "../types/NumberOfTrades.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// The cross process has completed for a specific security
struct CrossTradeMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    Quantity quantity;
    OrderBook order_book;
    CrossPrice cross_price;
    MatchNumber match_number;
    CrossType cross_type;
    NumberOfTrades number_of_trades;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'Q';

    // parse method
    static CrossTradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<CrossTradeMessage*>(buffer);
    }

    // parse method const
    static const CrossTradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const CrossTradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const CrossTradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const CrossTradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
