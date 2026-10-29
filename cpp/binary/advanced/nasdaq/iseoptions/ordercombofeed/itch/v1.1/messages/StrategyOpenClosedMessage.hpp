#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/OpenState.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

namespace itch_ordercombofeed = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

#pragma pack(push, 1)

// Strategy Open Closed Message
struct strategy_open_closed_message {

    struct fields_type {
        itch_ordercombofeed::timestamp timestamp;
        itch_ordercombofeed::strategy_id strategy_id;
        itch_ordercombofeed::open_state open_state;
    };

    itch_ordercombofeed::message_header header = {std::uint16_t(sizeof(itch_ordercombofeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::strategy_open_closed_message};

    fields_type fields;

    // parse method
    static strategy_open_closed_message* parse(std::byte* buffer) {
        return reinterpret_cast<strategy_open_closed_message*>(buffer);
    }

    // parse method const
    static const strategy_open_closed_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const strategy_open_closed_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(strategy_open_closed_message::fields_type, timestamp) == 0, "unexpected offset of strategy_open_closed_message::fields_type::timestamp");
static_assert(offsetof(strategy_open_closed_message::fields_type, strategy_id) == 6, "unexpected offset of strategy_open_closed_message::fields_type::strategy_id");
static_assert(offsetof(strategy_open_closed_message::fields_type, open_state) == 10, "unexpected offset of strategy_open_closed_message::fields_type::open_state");
static_assert(sizeof(strategy_open_closed_message::fields_type) == 11, "unexpected sizeof strategy_open_closed_message::fields_type");
static_assert(sizeof(strategy_open_closed_message) == sizeof(itch_ordercombofeed::message_header) + 11, "unexpected sizeof strategy_open_closed_message");

#pragma pack(pop)
}
