#pragma once

#include "../types/Timestamp.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/OrderReferenceNumber.hpp"
#include "../types/TradeType.hpp"
#include "../types/Quantity.hpp"
#include "../types/OrderBook.hpp"
#include "../types/MatchNumber.hpp"
#include "../types/TradePrice.hpp"
#include "../types/ParticipantIdBuyer.hpp"
#include "../types/ParticipantIdSeller.hpp"
#include "../structs/MessageHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

#pragma pack(push, 1)

// Execution details for a match involving non displayable order types
struct TradeMessage {

    Timestamp timestamp;
    TrackingNumber tracking_number;
    OrderReferenceNumber order_reference_number;
    TradeType trade_type;
    Quantity quantity;
    OrderBook order_book;
    MatchNumber match_number;
    TradePrice trade_price;
    ParticipantIdBuyer participant_id_buyer;
    ParticipantIdSeller participant_id_seller;

    // the type code that selects this message in the dispatch switch
    static constexpr char message_type = 'P';

    // parse method
    static TradeMessage* parse(std::byte* buffer) {
        return reinterpret_cast<TradeMessage*>(buffer);
    }

    // parse method const
    static const TradeMessage* parse(const std::byte* buffer) {
        return reinterpret_cast<const TradeMessage*>(buffer);
    }

    // parse the overlaid body from its selecting header
    static const TradeMessage* parse(const MessageHeader* header) {
        return reinterpret_cast<const TradeMessage*>(reinterpret_cast<const std::byte*>(header) + sizeof(MessageHeader));
    }
};

#pragma pack(pop)
}
