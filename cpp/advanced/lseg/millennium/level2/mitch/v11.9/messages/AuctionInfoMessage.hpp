#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/PairedQuantity.hpp"
#include "../types/Reserved4.hpp"
#include "../types/Reserved1.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../types/AuctionType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Auction Info Message
struct auction_info_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::paired_quantity paired_quantity;
        mitch_level2::reserved_4 reserved_4;
        mitch_level2::reserved_1 reserved_1;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::reserved_a reserved_a;
        mitch_level2::reserved_b reserved_b;
        mitch_level2::price price;
        mitch_level2::auction_type auction_type;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::auction_info_message};

    fields_type fields;

    // parse method
    static auction_info_message* parse(std::byte* buffer) {
        return reinterpret_cast<auction_info_message*>(buffer);
    }

    // parse method const
    static const auction_info_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const auction_info_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(auction_info_message::fields_type, nanosecond) == 0, "unexpected offset of auction_info_message::fields_type::nanosecond");
static_assert(offsetof(auction_info_message::fields_type, paired_quantity) == 4, "unexpected offset of auction_info_message::fields_type::paired_quantity");
static_assert(offsetof(auction_info_message::fields_type, reserved_4) == 8, "unexpected offset of auction_info_message::fields_type::reserved_4");
static_assert(offsetof(auction_info_message::fields_type, reserved_1) == 12, "unexpected offset of auction_info_message::fields_type::reserved_1");
static_assert(offsetof(auction_info_message::fields_type, instrument_id) == 13, "unexpected offset of auction_info_message::fields_type::instrument_id");
static_assert(offsetof(auction_info_message::fields_type, reserved_a) == 17, "unexpected offset of auction_info_message::fields_type::reserved_a");
static_assert(offsetof(auction_info_message::fields_type, reserved_b) == 18, "unexpected offset of auction_info_message::fields_type::reserved_b");
static_assert(offsetof(auction_info_message::fields_type, price) == 19, "unexpected offset of auction_info_message::fields_type::price");
static_assert(offsetof(auction_info_message::fields_type, auction_type) == 27, "unexpected offset of auction_info_message::fields_type::auction_type");
static_assert(sizeof(auction_info_message::fields_type) == 28, "unexpected sizeof auction_info_message::fields_type");
static_assert(sizeof(auction_info_message) == sizeof(mitch_level2::message_header) + 28, "unexpected sizeof auction_info_message");

#pragma pack(pop)
}
