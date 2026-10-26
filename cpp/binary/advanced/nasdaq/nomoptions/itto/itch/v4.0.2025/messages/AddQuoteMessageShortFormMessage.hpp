#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"
#include "../types/OptionId.hpp"
#include "../types/BidPriceShort.hpp"
#include "../types/BidSizeShort.hpp"
#include "../types/AskPriceShort.hpp"
#include "../types/AskSizeShort.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Add Quote Message Short Form Message
struct add_quote_message_short_form_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::bid_reference_number bid_reference_number;
        itch_itto::ask_reference_number ask_reference_number;
        itch_itto::option_id option_id;
        itch_itto::bid_price_short bid_price_short;
        itch_itto::bid_size_short bid_size_short;
        itch_itto::ask_price_short ask_price_short;
        itch_itto::ask_size_short ask_size_short;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::add_quote_message_short_form_message};

    fields_type fields;

    // parse method
    static add_quote_message_short_form_message* parse(std::byte* buffer) {
        return reinterpret_cast<add_quote_message_short_form_message*>(buffer);
    }

    // parse method const
    static const add_quote_message_short_form_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const add_quote_message_short_form_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(add_quote_message_short_form_message::fields_type, tracking_number) == 0, "unexpected offset of add_quote_message_short_form_message::fields_type::tracking_number");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, timestamp) == 2, "unexpected offset of add_quote_message_short_form_message::fields_type::timestamp");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, bid_reference_number) == 8, "unexpected offset of add_quote_message_short_form_message::fields_type::bid_reference_number");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, ask_reference_number) == 16, "unexpected offset of add_quote_message_short_form_message::fields_type::ask_reference_number");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, option_id) == 24, "unexpected offset of add_quote_message_short_form_message::fields_type::option_id");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, bid_price_short) == 28, "unexpected offset of add_quote_message_short_form_message::fields_type::bid_price_short");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, bid_size_short) == 30, "unexpected offset of add_quote_message_short_form_message::fields_type::bid_size_short");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, ask_price_short) == 32, "unexpected offset of add_quote_message_short_form_message::fields_type::ask_price_short");
static_assert(offsetof(add_quote_message_short_form_message::fields_type, ask_size_short) == 34, "unexpected offset of add_quote_message_short_form_message::fields_type::ask_size_short");
static_assert(sizeof(add_quote_message_short_form_message::fields_type) == 36, "unexpected sizeof add_quote_message_short_form_message::fields_type");
static_assert(sizeof(add_quote_message_short_form_message) == sizeof(itch_itto::message_header) + 36, "unexpected sizeof add_quote_message_short_form_message");

#pragma pack(pop)
}
