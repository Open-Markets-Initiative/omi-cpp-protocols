#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanosecond.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/ReservedA.hpp"
#include "../types/ReservedB.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/SymbolStatusFlags.hpp"
#include "../types/Reason.hpp"
#include "../types/SessionChangeReason.hpp"
#include "../types/NewEndTime.hpp"
#include "../types/BookType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

#pragma pack(push, 1)

// Symbol Status Message
struct symbol_status_message {

    struct fields_type {
        mitch_level2::nanosecond nanosecond;
        mitch_level2::instrument_id instrument_id;
        mitch_level2::reserved_a reserved_a;
        mitch_level2::reserved_b reserved_b;
        mitch_level2::trading_status trading_status;
        mitch_level2::symbol_status_flags symbol_status_flags;
        mitch_level2::reason reason;
        mitch_level2::session_change_reason session_change_reason;
        mitch_level2::new_end_time new_end_time;
        mitch_level2::book_type book_type;
    };

    mitch_level2::message_header header = {std::uint16_t(sizeof(mitch_level2::message_header) + sizeof(fields_type)), message_type::enum_type::symbol_status_message};

    fields_type fields;

    // parse method
    static symbol_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_status_message*>(buffer);
    }

    // parse method const
    static const symbol_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_status_message::fields_type, nanosecond) == 0, "unexpected offset of symbol_status_message::fields_type::nanosecond");
static_assert(offsetof(symbol_status_message::fields_type, instrument_id) == 4, "unexpected offset of symbol_status_message::fields_type::instrument_id");
static_assert(offsetof(symbol_status_message::fields_type, reserved_a) == 8, "unexpected offset of symbol_status_message::fields_type::reserved_a");
static_assert(offsetof(symbol_status_message::fields_type, reserved_b) == 9, "unexpected offset of symbol_status_message::fields_type::reserved_b");
static_assert(offsetof(symbol_status_message::fields_type, trading_status) == 10, "unexpected offset of symbol_status_message::fields_type::trading_status");
static_assert(offsetof(symbol_status_message::fields_type, symbol_status_flags) == 11, "unexpected offset of symbol_status_message::fields_type::symbol_status_flags");
static_assert(offsetof(symbol_status_message::fields_type, reason) == 12, "unexpected offset of symbol_status_message::fields_type::reason");
static_assert(offsetof(symbol_status_message::fields_type, session_change_reason) == 16, "unexpected offset of symbol_status_message::fields_type::session_change_reason");
static_assert(offsetof(symbol_status_message::fields_type, new_end_time) == 17, "unexpected offset of symbol_status_message::fields_type::new_end_time");
static_assert(offsetof(symbol_status_message::fields_type, book_type) == 25, "unexpected offset of symbol_status_message::fields_type::book_type");
static_assert(sizeof(symbol_status_message::fields_type) == 26, "unexpected sizeof symbol_status_message::fields_type");
static_assert(sizeof(symbol_status_message) == sizeof(mitch_level2::message_header) + 26, "unexpected sizeof symbol_status_message");

#pragma pack(pop)
}
