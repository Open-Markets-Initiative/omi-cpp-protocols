#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/TimeOffset.hpp"
#include "../types/Symbol.hpp"
#include "../types/TradeDate.hpp"
#include "../types/SettlementPrice.hpp"
#include "../types/Issue.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

namespace pitch_multicastdepthofbook = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

#pragma pack(push, 1)

// Settlement Message
struct settlement_message {

    struct fields_type {
        pitch_multicastdepthofbook::time_offset time_offset;
        pitch_multicastdepthofbook::symbol symbol;
        pitch_multicastdepthofbook::trade_date trade_date;
        pitch_multicastdepthofbook::settlement_price settlement_price;
        pitch_multicastdepthofbook::issue issue;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::settlement_message};

    fields_type fields;

    // parse method
    static settlement_message* parse(std::byte* buffer) {
        return reinterpret_cast<settlement_message*>(buffer);
    }

    // parse method const
    static const settlement_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const settlement_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(settlement_message::fields_type, time_offset) == 0, "unexpected offset of settlement_message::fields_type::time_offset");
static_assert(offsetof(settlement_message::fields_type, symbol) == 4, "unexpected offset of settlement_message::fields_type::symbol");
static_assert(offsetof(settlement_message::fields_type, trade_date) == 10, "unexpected offset of settlement_message::fields_type::trade_date");
static_assert(offsetof(settlement_message::fields_type, settlement_price) == 14, "unexpected offset of settlement_message::fields_type::settlement_price");
static_assert(offsetof(settlement_message::fields_type, issue) == 22, "unexpected offset of settlement_message::fields_type::issue");
static_assert(sizeof(settlement_message::fields_type) == 23, "unexpected sizeof settlement_message::fields_type");
static_assert(sizeof(settlement_message) == sizeof(pitch_multicastdepthofbook::message_header) + 23, "unexpected sizeof settlement_message");

#pragma pack(pop)
}
