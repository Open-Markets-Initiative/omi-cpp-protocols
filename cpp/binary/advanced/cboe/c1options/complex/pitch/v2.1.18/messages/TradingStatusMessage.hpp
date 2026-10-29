#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/ComplexSymbolId.hpp"
#include "../types/Unused.hpp"
#include "../types/TradingStatus.hpp"
#include "../types/Reserved1.hpp"
#include "../types/GthTradingStatus.hpp"
#include "../types/Padding.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Trading Status Message
struct trading_status_message {

    struct fields_type {
        pitch_complex::time_offset time_offset;
        pitch_complex::complex_symbol_id complex_symbol_id;
        pitch_complex::unused unused;
        pitch_complex::trading_status trading_status;
        pitch_complex::reserved_1 reserved_1;
        pitch_complex::gth_trading_status gth_trading_status;
        pitch_complex::padding padding;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::trading_status_message};

    fields_type fields;

    // parse method
    static trading_status_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_status_message*>(buffer);
    }

    // parse method const
    static const trading_status_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_status_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_status_message::fields_type, time_offset) == 0, "unexpected offset of trading_status_message::fields_type::time_offset");
static_assert(offsetof(trading_status_message::fields_type, complex_symbol_id) == 4, "unexpected offset of trading_status_message::fields_type::complex_symbol_id");
static_assert(offsetof(trading_status_message::fields_type, unused) == 10, "unexpected offset of trading_status_message::fields_type::unused");
static_assert(offsetof(trading_status_message::fields_type, trading_status) == 12, "unexpected offset of trading_status_message::fields_type::trading_status");
static_assert(offsetof(trading_status_message::fields_type, reserved_1) == 13, "unexpected offset of trading_status_message::fields_type::reserved_1");
static_assert(offsetof(trading_status_message::fields_type, gth_trading_status) == 14, "unexpected offset of trading_status_message::fields_type::gth_trading_status");
static_assert(offsetof(trading_status_message::fields_type, padding) == 15, "unexpected offset of trading_status_message::fields_type::padding");
static_assert(sizeof(trading_status_message::fields_type) == 16, "unexpected sizeof trading_status_message::fields_type");
static_assert(sizeof(trading_status_message) == sizeof(pitch_complex::message_header) + 16, "unexpected sizeof trading_status_message");

#pragma pack(pop)
}
