#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Offset1Padding3.hpp"
#include "../types/MdEntryTimestamp.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)

// Channel Reset 11 Message
struct channel_reset_11_message {

    struct fields_type {
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::offset_1_padding_3 offset_1_padding_3;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static channel_reset_11_message* parse(std::byte* buffer) {
        return reinterpret_cast<channel_reset_11_message*>(buffer);
    }

    // parse method const
    static const channel_reset_11_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const channel_reset_11_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(channel_reset_11_message::fields_type, match_event_indicator) == 0, "unexpected offset of channel_reset_11_message::fields_type::match_event_indicator");
static_assert(offsetof(channel_reset_11_message::fields_type, offset_1_padding_3) == 1, "unexpected offset of channel_reset_11_message::fields_type::offset_1_padding_3");
static_assert(offsetof(channel_reset_11_message::fields_type, md_entry_timestamp) == 4, "unexpected offset of channel_reset_11_message::fields_type::md_entry_timestamp");
static_assert(sizeof(channel_reset_11_message::fields_type) == 12, "unexpected sizeof channel_reset_11_message::fields_type");
static_assert(sizeof(channel_reset_11_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 12, "unexpected sizeof channel_reset_11_message");

#pragma pack(pop)
}
