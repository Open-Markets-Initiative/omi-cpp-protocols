#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/SymbolStatus.hpp"
#include "../types/Isin.hpp"
#include "../types/Sedol.hpp"
#include "../types/Segment.hpp"
#include "../types/Underlying.hpp"
#include "../types/Currency.hpp"
#include "../types/ReservedByte.hpp"
#include "../types/Reserved4.hpp"
#include "../types/PreviousClosePrice.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Symbol Directory Message
struct symbol_directory_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::reserved_a reserved_a;
        mitch_level2::reserved_b reserved_b;
        mitch_level2::symbol_status symbol_status;
        mitch_level2::isin isin;
        mitch_level2::sedol sedol;
        mitch_level2::segment segment;
        mitch_level2::underlying underlying;
        mitch_level2::currency currency;
        mitch_level2::reserved_byte reserved_byte;
        mitch_level2::reserved_4 reserved_4;
        mitch_level2::previous_close_price previous_close_price;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::symbol_directory_message};

    fields_type fields;

    // parse method
    static symbol_directory_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_directory_message*>(buffer);
    }

    // parse method const
    static const symbol_directory_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_directory_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_directory_message::fields_type, nanosecond) == 0, "unexpected offset of symbol_directory_message::fields_type::nanosecond");
static_assert(offsetof(symbol_directory_message::fields_type, instrument_id) == 4, "unexpected offset of symbol_directory_message::fields_type::instrument_id");
static_assert(offsetof(symbol_directory_message::fields_type, reserved_a) == 8, "unexpected offset of symbol_directory_message::fields_type::reserved_a");
static_assert(offsetof(symbol_directory_message::fields_type, reserved_b) == 9, "unexpected offset of symbol_directory_message::fields_type::reserved_b");
static_assert(offsetof(symbol_directory_message::fields_type, symbol_status) == 10, "unexpected offset of symbol_directory_message::fields_type::symbol_status");
static_assert(offsetof(symbol_directory_message::fields_type, isin) == 11, "unexpected offset of symbol_directory_message::fields_type::isin");
static_assert(offsetof(symbol_directory_message::fields_type, sedol) == 23, "unexpected offset of symbol_directory_message::fields_type::sedol");
static_assert(offsetof(symbol_directory_message::fields_type, segment) == 35, "unexpected offset of symbol_directory_message::fields_type::segment");
static_assert(offsetof(symbol_directory_message::fields_type, underlying) == 41, "unexpected offset of symbol_directory_message::fields_type::underlying");
static_assert(offsetof(symbol_directory_message::fields_type, currency) == 47, "unexpected offset of symbol_directory_message::fields_type::currency");
static_assert(offsetof(symbol_directory_message::fields_type, reserved_byte) == 50, "unexpected offset of symbol_directory_message::fields_type::reserved_byte");
static_assert(offsetof(symbol_directory_message::fields_type, reserved_4) == 51, "unexpected offset of symbol_directory_message::fields_type::reserved_4");
static_assert(offsetof(symbol_directory_message::fields_type, previous_close_price) == 55, "unexpected offset of symbol_directory_message::fields_type::previous_close_price");
static_assert(sizeof(symbol_directory_message::fields_type) == 63, "unexpected sizeof symbol_directory_message::fields_type");
static_assert(sizeof(symbol_directory_message) == sizeof(mitch_level2::message_header) + 63, "unexpected sizeof symbol_directory_message");

#pragma pack(pop)
}
