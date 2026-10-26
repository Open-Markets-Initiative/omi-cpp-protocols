#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/ExecutedQuantity.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/Price.hpp"
#include "../types/TradeMatchId.hpp"
#include "../types/CrossType.hpp"
#include "../types/SubBook.hpp"
#include "../types/PtModFlags.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Trade Message
struct trade_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::executed_quantity executed_quantity;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::reserved_a reserved_a;
        mitch_level2::reserved_b reserved_b;
        mitch_level2::price price;
        mitch_level2::trade_match_id trade_match_id;
        mitch_level2::cross_type cross_type;
        mitch_level2::sub_book sub_book;
        mitch_level2::pt_mod_flags pt_mod_flags;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::trade_message};

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
static_assert(offsetof(trade_message::fields_type, nanosecond) == 0, "unexpected offset of trade_message::fields_type::nanosecond");
static_assert(offsetof(trade_message::fields_type, executed_quantity) == 4, "unexpected offset of trade_message::fields_type::executed_quantity");
static_assert(offsetof(trade_message::fields_type, instrument_id) == 8, "unexpected offset of trade_message::fields_type::instrument_id");
static_assert(offsetof(trade_message::fields_type, reserved_a) == 12, "unexpected offset of trade_message::fields_type::reserved_a");
static_assert(offsetof(trade_message::fields_type, reserved_b) == 13, "unexpected offset of trade_message::fields_type::reserved_b");
static_assert(offsetof(trade_message::fields_type, price) == 14, "unexpected offset of trade_message::fields_type::price");
static_assert(offsetof(trade_message::fields_type, trade_match_id) == 22, "unexpected offset of trade_message::fields_type::trade_match_id");
static_assert(offsetof(trade_message::fields_type, cross_type) == 30, "unexpected offset of trade_message::fields_type::cross_type");
static_assert(offsetof(trade_message::fields_type, sub_book) == 31, "unexpected offset of trade_message::fields_type::sub_book");
static_assert(offsetof(trade_message::fields_type, pt_mod_flags) == 32, "unexpected offset of trade_message::fields_type::pt_mod_flags");
static_assert(sizeof(trade_message::fields_type) == 33, "unexpected sizeof trade_message::fields_type");
static_assert(sizeof(trade_message) == sizeof(mitch_level2::message_header) + 33, "unexpected sizeof trade_message");

#pragma pack(pop)
}
