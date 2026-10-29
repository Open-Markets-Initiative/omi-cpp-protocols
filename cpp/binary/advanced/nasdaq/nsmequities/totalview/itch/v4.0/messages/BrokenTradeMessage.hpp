#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Nanoseconds.hpp"
#include "../types/MatchNumber.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

namespace itch_totalview = ::nasdaq::nsmequities::totalview::itch::v4_0;

#pragma pack(push, 1)

// Broken Trade Message
struct broken_trade_message {

    struct fields_type {
        itch_totalview::nanoseconds nanoseconds;
        itch_totalview::match_number match_number;
    };

    itch_totalview::message_header header = {std::uint16_t(sizeof(itch_totalview::message_header) + sizeof(fields_type) - 2), message_type::enum_type::broken_trade_message};

    fields_type fields;

    // parse method
    static broken_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<broken_trade_message*>(buffer);
    }

    // parse method const
    static const broken_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const broken_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(broken_trade_message::fields_type, nanoseconds) == 0, "unexpected offset of broken_trade_message::fields_type::nanoseconds");
static_assert(offsetof(broken_trade_message::fields_type, match_number) == 4, "unexpected offset of broken_trade_message::fields_type::match_number");
static_assert(sizeof(broken_trade_message::fields_type) == 12, "unexpected sizeof broken_trade_message::fields_type");
static_assert(sizeof(broken_trade_message) == sizeof(itch_totalview::message_header) + 12, "unexpected sizeof broken_trade_message");

#pragma pack(pop)
}
