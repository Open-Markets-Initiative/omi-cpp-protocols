#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/ComplexInstrumentId.hpp"
#include "../types/AuctionId.hpp"
#include "../types/AuctionType.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/Price.hpp"
#include "../types/Quantity.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/AuctionEndOffset.hpp"
#include "../types/ClientId.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Auction Notification Message
struct auction_notification_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::complex_instrument_id complex_instrument_id;
        pitch_complex::auction_id auction_id;
        pitch_complex::auction_type auction_type;
        pitch_complex::side_indicator side_indicator;
        pitch_complex::price price;
        pitch_complex::quantity quantity;
        pitch_complex::customer_indicator customer_indicator;
        pitch_complex::participant_id participant_id;
        pitch_complex::auction_end_offset auction_end_offset;
        pitch_complex::client_id client_id;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::auction_notification_message};

    fields_type fields;

    // parse method
    static auction_notification_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_notification_message*>(buffer);
    }

    // parse method const
    static const auction_notification_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_notification_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_notification_message::fields_type, time_offset) == 0, "unexpected offset of auction_notification_message::fields_type::time_offset");
static_assert(offsetof(auction_notification_message::fields_type, complex_instrument_id) == 4, "unexpected offset of auction_notification_message::fields_type::complex_instrument_id");
static_assert(offsetof(auction_notification_message::fields_type, auction_id) == 10, "unexpected offset of auction_notification_message::fields_type::auction_id");
static_assert(offsetof(auction_notification_message::fields_type, auction_type) == 18, "unexpected offset of auction_notification_message::fields_type::auction_type");
static_assert(offsetof(auction_notification_message::fields_type, side_indicator) == 19, "unexpected offset of auction_notification_message::fields_type::side_indicator");
static_assert(offsetof(auction_notification_message::fields_type, price) == 20, "unexpected offset of auction_notification_message::fields_type::price");
static_assert(offsetof(auction_notification_message::fields_type, quantity) == 28, "unexpected offset of auction_notification_message::fields_type::quantity");
static_assert(offsetof(auction_notification_message::fields_type, customer_indicator) == 32, "unexpected offset of auction_notification_message::fields_type::customer_indicator");
static_assert(offsetof(auction_notification_message::fields_type, participant_id) == 33, "unexpected offset of auction_notification_message::fields_type::participant_id");
static_assert(offsetof(auction_notification_message::fields_type, auction_end_offset) == 37, "unexpected offset of auction_notification_message::fields_type::auction_end_offset");
static_assert(offsetof(auction_notification_message::fields_type, client_id) == 41, "unexpected offset of auction_notification_message::fields_type::client_id");
static_assert(sizeof(auction_notification_message::fields_type) == 45, "unexpected sizeof auction_notification_message::fields_type");
static_assert(sizeof(auction_notification_message) == sizeof(pitch_complex::message_header) + 45, "unexpected sizeof auction_notification_message");

#pragma pack(pop)
}
