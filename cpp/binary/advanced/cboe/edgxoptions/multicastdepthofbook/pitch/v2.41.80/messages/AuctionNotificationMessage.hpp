#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/AuctionId.hpp"
#include "../types/AuctionType.hpp"
#include "../types/Side.hpp"
#include "../types/PriceLong.hpp"
#include "../types/Contracts.hpp"
#include "../types/CustomerIndicator.hpp"
#include "../types/ParticipantId.hpp"
#include "../types/AuctionEndOffset.hpp"
#include "../types/ClientId.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

#pragma pack(push, 1)

// Auction Notification Message
struct auction_notification_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::auction_id auction_id;
        pitch_multicastdepthofbook::auction_type auction_type;
        pitch_multicastdepthofbook::side side;
        pitch_multicastdepthofbook::price_long price_long;
        pitch_multicastdepthofbook::contracts contracts;
        pitch_multicastdepthofbook::customer_indicator customer_indicator;
        pitch_multicastdepthofbook::participant_id participant_id;
        pitch_multicastdepthofbook::auction_end_offset auction_end_offset;
        pitch_multicastdepthofbook::client_id client_id;
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
static_assert(offsetof(auction_notification_message::fields_type, side) == 19, "unexpected offset of auction_notification_message::fields_type::side");
static_assert(offsetof(auction_notification_message::fields_type, price_long) == 20, "unexpected offset of auction_notification_message::fields_type::price_long");
static_assert(offsetof(auction_notification_message::fields_type, contracts) == 28, "unexpected offset of auction_notification_message::fields_type::contracts");
static_assert(offsetof(auction_notification_message::fields_type, customer_indicator) == 32, "unexpected offset of auction_notification_message::fields_type::customer_indicator");
static_assert(offsetof(auction_notification_message::fields_type, participant_id) == 33, "unexpected offset of auction_notification_message::fields_type::participant_id");
static_assert(offsetof(auction_notification_message::fields_type, auction_end_offset) == 37, "unexpected offset of auction_notification_message::fields_type::auction_end_offset");
static_assert(offsetof(auction_notification_message::fields_type, client_id) == 41, "unexpected offset of auction_notification_message::fields_type::client_id");
static_assert(sizeof(auction_notification_message::fields_type) == 45, "unexpected sizeof auction_notification_message::fields_type");
static_assert(sizeof(auction_notification_message) == sizeof(pitch_multicastdepthofbook::message_header) + 45, "unexpected sizeof auction_notification_message");

#pragma pack(pop)
}
