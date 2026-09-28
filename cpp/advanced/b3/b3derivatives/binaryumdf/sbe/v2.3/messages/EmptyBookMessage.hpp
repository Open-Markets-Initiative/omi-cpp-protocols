#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../types/SecurityId.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/Offset9Padding3.hpp"
#include "../types/MdEntryTimestamp.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v2_3;

#pragma pack(push, 1)

// Empty Book Message
struct empty_book_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::match_event_indicator match_event_indicator;
        sbe_binaryumdf::offset_9_padding_3 offset_9_padding_3;
        sbe_binaryumdf::md_entry_timestamp md_entry_timestamp;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    fields_type fields;

    // parse method
    static empty_book_message* parse(std::byte* buffer) {
        return reinterpret_cast<empty_book_message*>(buffer);
    }

    // parse method const
    static const empty_book_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const empty_book_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(empty_book_message::fields_type, security_id) == 0, "unexpected offset of empty_book_message::fields_type::security_id");
static_assert(offsetof(empty_book_message::fields_type, match_event_indicator) == 8, "unexpected offset of empty_book_message::fields_type::match_event_indicator");
static_assert(offsetof(empty_book_message::fields_type, offset_9_padding_3) == 9, "unexpected offset of empty_book_message::fields_type::offset_9_padding_3");
static_assert(offsetof(empty_book_message::fields_type, md_entry_timestamp) == 12, "unexpected offset of empty_book_message::fields_type::md_entry_timestamp");
static_assert(sizeof(empty_book_message::fields_type) == 20, "unexpected sizeof empty_book_message::fields_type");
static_assert(sizeof(empty_book_message) == sizeof(sbe_binaryumdf::framing_header) + sizeof(sbe_binaryumdf::message_header) + 20, "unexpected sizeof empty_book_message");

#pragma pack(pop)
}
