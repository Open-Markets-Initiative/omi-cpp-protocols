#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/ResetStartEndFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Reset Message
struct reset_message {

    struct fields_type {
        flex_marketbyorder::reset_start_end_flag reset_start_end_flag;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::reset_message};

    fields_type fields;

    // parse method
    static reset_message* parse(std::byte* buffer) {
        return reinterpret_cast<reset_message*>(buffer);
    }

    // parse method const
    static const reset_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const reset_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(reset_message::fields_type, reset_start_end_flag) == 0, "unexpected offset of reset_message::fields_type::reset_start_end_flag");
static_assert(sizeof(reset_message::fields_type) == 1, "unexpected sizeof reset_message::fields_type");
static_assert(sizeof(reset_message) == sizeof(message_header) + 1, "unexpected sizeof reset_message");

#pragma pack(pop)
}
