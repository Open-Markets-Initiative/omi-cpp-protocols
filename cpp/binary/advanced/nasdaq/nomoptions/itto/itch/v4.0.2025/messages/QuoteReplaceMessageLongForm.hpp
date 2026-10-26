#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/OriginalBidReferenceNumber.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/OriginalAskReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"
#include "../types/BidPriceLong.hpp"
#include "../types/BidSizeLong.hpp"
#include "../types/AskPriceLong.hpp"
#include "../types/AskSizeLong.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Quote Replace Message Long Form
struct quote_replace_message_long_form {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::original_bid_reference_number original_bid_reference_number;
        itch_itto::bid_reference_number bid_reference_number;
        itch_itto::original_ask_reference_number original_ask_reference_number;
        itch_itto::ask_reference_number ask_reference_number;
        itch_itto::bid_price_long bid_price_long;
        itch_itto::bid_size_long bid_size_long;
        itch_itto::ask_price_long ask_price_long;
        itch_itto::ask_size_long ask_size_long;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::quote_replace_message_long_form};

    fields_type fields;

    // parse method
    static quote_replace_message_long_form* parse(std::byte* buffer) {
        return reinterpret_cast<quote_replace_message_long_form*>(buffer);
    }

    // parse method const
    static const quote_replace_message_long_form* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_replace_message_long_form*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_replace_message_long_form::fields_type, tracking_number) == 0, "unexpected offset of quote_replace_message_long_form::fields_type::tracking_number");
static_assert(offsetof(quote_replace_message_long_form::fields_type, timestamp) == 2, "unexpected offset of quote_replace_message_long_form::fields_type::timestamp");
static_assert(offsetof(quote_replace_message_long_form::fields_type, original_bid_reference_number) == 8, "unexpected offset of quote_replace_message_long_form::fields_type::original_bid_reference_number");
static_assert(offsetof(quote_replace_message_long_form::fields_type, bid_reference_number) == 16, "unexpected offset of quote_replace_message_long_form::fields_type::bid_reference_number");
static_assert(offsetof(quote_replace_message_long_form::fields_type, original_ask_reference_number) == 24, "unexpected offset of quote_replace_message_long_form::fields_type::original_ask_reference_number");
static_assert(offsetof(quote_replace_message_long_form::fields_type, ask_reference_number) == 32, "unexpected offset of quote_replace_message_long_form::fields_type::ask_reference_number");
static_assert(offsetof(quote_replace_message_long_form::fields_type, bid_price_long) == 40, "unexpected offset of quote_replace_message_long_form::fields_type::bid_price_long");
static_assert(offsetof(quote_replace_message_long_form::fields_type, bid_size_long) == 44, "unexpected offset of quote_replace_message_long_form::fields_type::bid_size_long");
static_assert(offsetof(quote_replace_message_long_form::fields_type, ask_price_long) == 48, "unexpected offset of quote_replace_message_long_form::fields_type::ask_price_long");
static_assert(offsetof(quote_replace_message_long_form::fields_type, ask_size_long) == 52, "unexpected offset of quote_replace_message_long_form::fields_type::ask_size_long");
static_assert(sizeof(quote_replace_message_long_form::fields_type) == 56, "unexpected sizeof quote_replace_message_long_form::fields_type");
static_assert(sizeof(quote_replace_message_long_form) == sizeof(itch_itto::message_header) + 56, "unexpected sizeof quote_replace_message_long_form");

#pragma pack(pop)
}
