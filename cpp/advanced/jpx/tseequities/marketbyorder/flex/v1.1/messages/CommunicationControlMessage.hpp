#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TestModeFlag.hpp"
#include "../types/CommunicationStartEndFlag.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

namespace flex_marketbyorder = ::jpx::tseequities::marketbyorder::flex::v1_1;

#pragma pack(push, 1)

// Communication Control Message
struct communication_control_message {

    struct fields_type {
        flex_marketbyorder::test_mode_flag test_mode_flag;
        flex_marketbyorder::communication_start_end_flag communication_start_end_flag;
    };

    message_header header = {std::uint16_t(sizeof(message_header) + sizeof(fields_type) - 1), message_type::enum_type::communication_control_message};

    fields_type fields;

    // parse method
    static communication_control_message* parse(std::byte* buffer) {
        return reinterpret_cast<communication_control_message*>(buffer);
    }

    // parse method const
    static const communication_control_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const communication_control_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(communication_control_message::fields_type, test_mode_flag) == 0, "unexpected offset of communication_control_message::fields_type::test_mode_flag");
static_assert(offsetof(communication_control_message::fields_type, communication_start_end_flag) == 1, "unexpected offset of communication_control_message::fields_type::communication_start_end_flag");
static_assert(sizeof(communication_control_message::fields_type) == 2, "unexpected sizeof communication_control_message::fields_type");
static_assert(sizeof(communication_control_message) == sizeof(message_header) + 2, "unexpected sizeof communication_control_message");

#pragma pack(pop)
}
