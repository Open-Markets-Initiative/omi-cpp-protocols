#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/TradeDate.hpp"
#include "../types/SourceId.hpp"
#include "../types/Text.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

namespace itch_ntp = ::asx::asxderivatives::ntp::itch::v1_05;

#pragma pack(push, 1)

// Text Message
struct text_message {

    struct fields_type {
        itch_ntp::nanoseconds nanoseconds;
        itch_ntp::trade_date trade_date;
        itch_ntp::source_id source_id;
        itch_ntp::text text;
    };

    itch_ntp::message_header header = {std::uint16_t(sizeof(itch_ntp::message_header) + sizeof(fields_type) - 2), message_type::enum_type::text_message};

    fields_type fields;

    // parse method
    static text_message* parse(std::byte* buffer) {
        return reinterpret_cast<text_message*>(buffer);
    }

    // parse method const
    static const text_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const text_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(text_message::fields_type, nanoseconds) == 0, "unexpected offset of text_message::fields_type::nanoseconds");
static_assert(offsetof(text_message::fields_type, trade_date) == 4, "unexpected offset of text_message::fields_type::trade_date");
static_assert(offsetof(text_message::fields_type, source_id) == 6, "unexpected offset of text_message::fields_type::source_id");
static_assert(offsetof(text_message::fields_type, text) == 12, "unexpected offset of text_message::fields_type::text");
static_assert(sizeof(text_message::fields_type) == 112, "unexpected sizeof text_message::fields_type");
static_assert(sizeof(text_message) == sizeof(itch_ntp::message_header) + 112, "unexpected sizeof text_message");

#pragma pack(pop)
}
