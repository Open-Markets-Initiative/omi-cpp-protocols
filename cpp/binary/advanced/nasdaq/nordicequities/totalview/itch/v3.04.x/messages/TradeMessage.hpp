#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
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

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

#pragma pack(push, 1)

// Trade Message
struct trade_message {

    struct fields_type {
        itch_totalview::timestamp timestamp;
        itch_totalview::tracking_number tracking_number;
        itch_totalview::order_reference_number order_reference_number;
        itch_totalview::trade_type trade_type;
        itch_totalview::quantity quantity;
        itch_totalview::order_book order_book;
        itch_totalview::match_number match_number;
        itch_totalview::trade_price trade_price;
        itch_totalview::participant_id_buyer participant_id_buyer;
        itch_totalview::participant_id_seller participant_id_seller;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::trade_message};

    fields_type fields;

    // parse method
    static trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_message*>(buffer);
    }

    // parse method const
    static const trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_message::fields_type, timestamp) == 0, "unexpected offset of trade_message::fields_type::timestamp");
static_assert(offsetof(trade_message::fields_type, tracking_number) == 8, "unexpected offset of trade_message::fields_type::tracking_number");
static_assert(offsetof(trade_message::fields_type, order_reference_number) == 10, "unexpected offset of trade_message::fields_type::order_reference_number");
static_assert(offsetof(trade_message::fields_type, trade_type) == 18, "unexpected offset of trade_message::fields_type::trade_type");
static_assert(offsetof(trade_message::fields_type, quantity) == 19, "unexpected offset of trade_message::fields_type::quantity");
static_assert(offsetof(trade_message::fields_type, order_book) == 23, "unexpected offset of trade_message::fields_type::order_book");
static_assert(offsetof(trade_message::fields_type, match_number) == 27, "unexpected offset of trade_message::fields_type::match_number");
static_assert(offsetof(trade_message::fields_type, trade_price) == 31, "unexpected offset of trade_message::fields_type::trade_price");
static_assert(offsetof(trade_message::fields_type, participant_id_buyer) == 35, "unexpected offset of trade_message::fields_type::participant_id_buyer");
static_assert(offsetof(trade_message::fields_type, participant_id_seller) == 39, "unexpected offset of trade_message::fields_type::participant_id_seller");
static_assert(sizeof(trade_message::fields_type) == 43, "unexpected sizeof trade_message::fields_type");
static_assert(sizeof(trade_message) == sizeof(itch_totalview::message_header) + 43, "unexpected sizeof trade_message");

#pragma pack(pop)
}
