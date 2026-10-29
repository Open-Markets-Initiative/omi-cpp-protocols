#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

#pragma pack(push, 1)

// Transaction Begin
struct transaction_begin {

    struct fields_type {
        pitch_complex::time_offset time_offset;
    };

    pitch_complex::message_header header = {std::uint16_t(sizeof(pitch_complex::message_header) + sizeof(fields_type)), message_type::enum_type::transaction_begin};

    fields_type fields;

    // parse method
    static transaction_begin* parse(std::byte* buffer) {
        return reinterpret_cast<transaction_begin*>(buffer);
    }

    // parse method const
    static const transaction_begin* parse(const std::byte* buffer) {
        return reinterpret_cast<const transaction_begin*>(buffer);
    }

};

// layout verification
static_assert(offsetof(transaction_begin::fields_type, time_offset) == 0, "unexpected offset of transaction_begin::fields_type::time_offset");
static_assert(sizeof(transaction_begin::fields_type) == 4, "unexpected sizeof transaction_begin::fields_type");
static_assert(sizeof(transaction_begin) == sizeof(pitch_complex::message_header) + 4, "unexpected sizeof transaction_begin");

#pragma pack(pop)
}
