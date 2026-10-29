#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/AuctionId.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Auction Cancel Message
struct auction_cancel_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::auction_id auction_id;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::auction_cancel_message};

    fields_type fields;

    // parse method
    static auction_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_cancel_message*>(buffer);
    }

    // parse method const
    static const auction_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_cancel_message::fields_type, time_offset) == 0, "unexpected offset of auction_cancel_message::fields_type::time_offset");
static_assert(offsetof(auction_cancel_message::fields_type, auction_id) == 4, "unexpected offset of auction_cancel_message::fields_type::auction_id");
static_assert(sizeof(auction_cancel_message::fields_type) == 12, "unexpected sizeof auction_cancel_message::fields_type");
static_assert(sizeof(auction_cancel_message) == sizeof(pitch_complex::message_header) + 12, "unexpected sizeof auction_cancel_message");

#pragma pack(pop)
}
