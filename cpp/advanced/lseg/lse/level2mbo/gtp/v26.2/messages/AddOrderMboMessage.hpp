#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OrderId.hpp"
#include "../types/Side.hpp"
#include "../types/SizeType.hpp"
#include "../types/Instrument.hpp"
#include "../types/Price.hpp"
#include "../types/Reserved8.hpp"
#include "../types/SourceVenue.hpp"
#include "../types/OrderBookType.hpp"
#include "../types/Participant.hpp"
#include "../types/Depth.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

namespace gtp_level2mbo = ::lseg::lse::level2mbo::gtp::v26_2;

#pragma pack(push, 1)

// Add Order Mbo Message
struct add_order_mbo_message {

    struct fields_type {
        gtp_level2mbo::timestamp timestamp;
        gtp_level2mbo::order_id order_id;
        gtp_level2mbo::side side;
        gtp_level2mbo::size_type size;
        gtp_level2mbo::instrument instrument;
        gtp_level2mbo::price price;
        gtp_level2mbo::reserved_8 reserved_8;
        gtp_level2mbo::source_venue source_venue;
        gtp_level2mbo::order_book_type order_book_type;
        gtp_level2mbo::participant participant;
        gtp_level2mbo::depth depth;
    };

    gtp_level2mbo::message_header header = {std::uint16_t(sizeof(gtp_level2mbo::message_header) + sizeof(fields_type)), message_type::enum_type::add_order_mbo_message};

    fields_type fields;

    // parse method
    static add_order_mbo_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_order_mbo_message*>(buffer);
    }

    // parse method const
    static const add_order_mbo_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_order_mbo_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_order_mbo_message::fields_type, timestamp) == 0, "unexpected offset of add_order_mbo_message::fields_type::timestamp");
static_assert(offsetof(add_order_mbo_message::fields_type, order_id) == 8, "unexpected offset of add_order_mbo_message::fields_type::order_id");
static_assert(offsetof(add_order_mbo_message::fields_type, side) == 16, "unexpected offset of add_order_mbo_message::fields_type::side");
static_assert(offsetof(add_order_mbo_message::fields_type, size) == 17, "unexpected offset of add_order_mbo_message::fields_type::size");
static_assert(offsetof(add_order_mbo_message::fields_type, instrument) == 25, "unexpected offset of add_order_mbo_message::fields_type::instrument");
static_assert(offsetof(add_order_mbo_message::fields_type, price) == 33, "unexpected offset of add_order_mbo_message::fields_type::price");
static_assert(offsetof(add_order_mbo_message::fields_type, reserved_8) == 41, "unexpected offset of add_order_mbo_message::fields_type::reserved_8");
static_assert(offsetof(add_order_mbo_message::fields_type, source_venue) == 49, "unexpected offset of add_order_mbo_message::fields_type::source_venue");
static_assert(offsetof(add_order_mbo_message::fields_type, order_book_type) == 51, "unexpected offset of add_order_mbo_message::fields_type::order_book_type");
static_assert(offsetof(add_order_mbo_message::fields_type, participant) == 52, "unexpected offset of add_order_mbo_message::fields_type::participant");
static_assert(offsetof(add_order_mbo_message::fields_type, depth) == 63, "unexpected offset of add_order_mbo_message::fields_type::depth");
static_assert(sizeof(add_order_mbo_message::fields_type) == 64, "unexpected sizeof add_order_mbo_message::fields_type");
static_assert(sizeof(add_order_mbo_message) == sizeof(gtp_level2mbo::message_header) + 64, "unexpected sizeof add_order_mbo_message");

#pragma pack(pop)
}
