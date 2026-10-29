#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Reserved2.hpp"
#include "../types/Timestamp.hpp"
#include "../types/Event.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// Market Event Message
struct market_event_message {

    struct fields_type {
        aspen_marketdatafeed::reserved_2 reserved_2;
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::event event;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::market_event_message};

    fields_type fields;

    // parse method
    static market_event_message* parse(std::byte* buffer) {
        return reinterpret_cast<market_event_message*>(buffer);
    }

    // parse method const
    static const market_event_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const market_event_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(market_event_message::fields_type, reserved_2) == 0, "unexpected offset of market_event_message::fields_type::reserved_2");
static_assert(offsetof(market_event_message::fields_type, timestamp) == 2, "unexpected offset of market_event_message::fields_type::timestamp");
static_assert(offsetof(market_event_message::fields_type, event) == 10, "unexpected offset of market_event_message::fields_type::event");
static_assert(sizeof(market_event_message::fields_type) == 11, "unexpected sizeof market_event_message::fields_type");
static_assert(sizeof(market_event_message) == sizeof(aspen_marketdatafeed::message_header) + 11, "unexpected sizeof market_event_message");

#pragma pack(pop)
}
