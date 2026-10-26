#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/BuyLimitPrice.hpp"
#include "../types/BuyLimitSize.hpp"
#include "../types/SellLimitPrice.hpp"
#include "../types/SellLimitSize.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Top Of Book Message
struct top_of_book_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::buy_limit_price buy_limit_price;
        mitch_level2::buy_limit_size buy_limit_size;
        mitch_level2::sell_limit_price sell_limit_price;
        mitch_level2::sell_limit_size sell_limit_size;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::top_of_book_message};

    fields_type fields;

    // parse method
    static top_of_book_message* parse(std::byte* buffer) {
        return reinterpret_cast<top_of_book_message*>(buffer);
    }

    // parse method const
    static const top_of_book_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const top_of_book_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(top_of_book_message::fields_type, nanosecond) == 0, "unexpected offset of top_of_book_message::fields_type::nanosecond");
static_assert(offsetof(top_of_book_message::fields_type, instrument_id) == 4, "unexpected offset of top_of_book_message::fields_type::instrument_id");
static_assert(offsetof(top_of_book_message::fields_type, buy_limit_price) == 8, "unexpected offset of top_of_book_message::fields_type::buy_limit_price");
static_assert(offsetof(top_of_book_message::fields_type, buy_limit_size) == 16, "unexpected offset of top_of_book_message::fields_type::buy_limit_size");
static_assert(offsetof(top_of_book_message::fields_type, sell_limit_price) == 20, "unexpected offset of top_of_book_message::fields_type::sell_limit_price");
static_assert(offsetof(top_of_book_message::fields_type, sell_limit_size) == 28, "unexpected offset of top_of_book_message::fields_type::sell_limit_size");
static_assert(sizeof(top_of_book_message::fields_type) == 32, "unexpected sizeof top_of_book_message::fields_type");
static_assert(sizeof(top_of_book_message) == sizeof(mitch_level2::message_header) + 32, "unexpected sizeof top_of_book_message");

#pragma pack(pop)
}
