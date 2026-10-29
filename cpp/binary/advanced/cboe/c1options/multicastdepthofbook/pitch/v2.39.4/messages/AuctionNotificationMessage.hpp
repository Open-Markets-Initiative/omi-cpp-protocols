#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/AuctionId.hpp"
#include "../types/AuctionType.hpp"
#include "../types/SideIndicator.hpp"
#include "../types/LongPrice.hpp"
#include "../types/Contracts.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/AuctionEndOffset.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

namespace pitch_multicastdepthofbook = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

#pragma pack(push, 1)

// Auction Notification Message
struct auction_notification_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::auction_id auction_id;
        pitch_multicastdepthofbook::auction_type auction_type;
        pitch_multicastdepthofbook::side_indicator side_indicator;
        pitch_multicastdepthofbook::long_price long_price;
        pitch_multicastdepthofbook::contracts contracts;
        pitch_multicastdepthofbook::customer_indicator customer_indicator;
        pitch_multicastdepthofbook::participant_id participant_id;
        pitch_multicastdepthofbook::auction_end_offset auction_end_offset;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::auction_notification_message};

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
static_assert(offsetof(auction_notification_message::fields_type, symbol) == 4, "unexpected offset of auction_notification_message::fields_type::symbol");
static_assert(offsetof(auction_notification_message::fields_type, auction_id) == 10, "unexpected offset of auction_notification_message::fields_type::auction_id");
static_assert(offsetof(auction_notification_message::fields_type, auction_type) == 18, "unexpected offset of auction_notification_message::fields_type::auction_type");
static_assert(offsetof(auction_notification_message::fields_type, side_indicator) == 19, "unexpected offset of auction_notification_message::fields_type::side_indicator");
static_assert(offsetof(auction_notification_message::fields_type, long_price) == 20, "unexpected offset of auction_notification_message::fields_type::long_price");
static_assert(offsetof(auction_notification_message::fields_type, contracts) == 28, "unexpected offset of auction_notification_message::fields_type::contracts");
static_assert(offsetof(auction_notification_message::fields_type, customer_indicator) == 32, "unexpected offset of auction_notification_message::fields_type::customer_indicator");
static_assert(offsetof(auction_notification_message::fields_type, participant_id) == 33, "unexpected offset of auction_notification_message::fields_type::participant_id");
static_assert(offsetof(auction_notification_message::fields_type, auction_end_offset) == 37, "unexpected offset of auction_notification_message::fields_type::auction_end_offset");
static_assert(sizeof(auction_notification_message::fields_type) == 41, "unexpected sizeof auction_notification_message::fields_type");
static_assert(sizeof(auction_notification_message) == sizeof(pitch_multicastdepthofbook::message_header) + 41, "unexpected sizeof auction_notification_message");

#pragma pack(pop)
}
