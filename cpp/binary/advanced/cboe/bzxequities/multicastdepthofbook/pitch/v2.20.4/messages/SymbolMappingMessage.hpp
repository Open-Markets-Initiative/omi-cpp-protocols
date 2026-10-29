#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/FeedSymbol.hpp"
#include "../types/OsiSymbol.hpp"
#include "../types/SymbolCondition.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

#pragma pack(push, 1)

// Symbol Mapping Message
struct symbol_mapping_message {

    struct fields_type {
        pitch_multicastdepthofbook::feed_symbol feed_symbol;
        pitch_multicastdepthofbook::osi_symbol osi_symbol;
        pitch_multicastdepthofbook::symbol_condition symbol_condition;
    };

    pitch_multicastdepthofbook::message_header header = {std::uint16_t(sizeof(pitch_multicastdepthofbook::message_header) + sizeof(fields_type)), message_type::enum_type::symbol_mapping_message};

    fields_type fields;

    // parse method
    static symbol_mapping_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_mapping_message*>(buffer);
    }

    // parse method const
    static const symbol_mapping_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_mapping_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_mapping_message::fields_type, feed_symbol) == 0, "unexpected offset of symbol_mapping_message::fields_type::feed_symbol");
static_assert(offsetof(symbol_mapping_message::fields_type, osi_symbol) == 6, "unexpected offset of symbol_mapping_message::fields_type::osi_symbol");
static_assert(offsetof(symbol_mapping_message::fields_type, symbol_condition) == 27, "unexpected offset of symbol_mapping_message::fields_type::symbol_condition");
static_assert(sizeof(symbol_mapping_message::fields_type) == 28, "unexpected sizeof symbol_mapping_message::fields_type");
static_assert(sizeof(symbol_mapping_message) == sizeof(pitch_multicastdepthofbook::message_header) + 28, "unexpected sizeof symbol_mapping_message");

#pragma pack(pop)
}
