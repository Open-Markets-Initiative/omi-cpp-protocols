#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TrackingNumber.hpp"
#include "../types/Timestamp.hpp"
#include "../types/BidReferenceNumber.hpp"
#include "../types/AskReferenceNumber.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

namespace itch_itto = ::nasdaq::nomoptions::itto::itch::v4_0_2025;

#pragma pack(push, 1)

// Quote Delete Message
struct quote_delete_message {

    struct fields_type {
        itch_itto::tracking_number tracking_number;
        itch_itto::timestamp timestamp;
        itch_itto::bid_reference_number bid_reference_number;
        itch_itto::ask_reference_number ask_reference_number;
    };

    itch_itto::message_header header = {std::uint16_t(sizeof(itch_itto::message_header) + sizeof(fields_type) - 2), message_type::enum_type::quote_delete_message};

    fields_type fields;

    // parse method
    static quote_delete_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_delete_message*>(buffer);
    }

    // parse method const
    static const quote_delete_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_delete_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_delete_message::fields_type, tracking_number) == 0, "unexpected offset of quote_delete_message::fields_type::tracking_number");
static_assert(offsetof(quote_delete_message::fields_type, timestamp) == 2, "unexpected offset of quote_delete_message::fields_type::timestamp");
static_assert(offsetof(quote_delete_message::fields_type, bid_reference_number) == 8, "unexpected offset of quote_delete_message::fields_type::bid_reference_number");
static_assert(offsetof(quote_delete_message::fields_type, ask_reference_number) == 16, "unexpected offset of quote_delete_message::fields_type::ask_reference_number");
static_assert(sizeof(quote_delete_message::fields_type) == 24, "unexpected sizeof quote_delete_message::fields_type");
static_assert(sizeof(quote_delete_message) == sizeof(itch_itto::message_header) + 24, "unexpected sizeof quote_delete_message");

#pragma pack(pop)
}
