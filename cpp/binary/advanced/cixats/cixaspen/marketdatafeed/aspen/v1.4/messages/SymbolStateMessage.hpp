#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/SymbolId.hpp"
#include "../types/Symbol.hpp"
#include "../types/State.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Info.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

#pragma pack(push, 1)

// Symbol State Message
struct symbol_state_message {

    struct fields_type {
        aspen_marketdatafeed::timestamp timestamp;
        aspen_marketdatafeed::symbol_id symbol_id;
        aspen_marketdatafeed::symbol symbol;
        aspen_marketdatafeed::state state;
        aspen_marketdatafeed::reserved_1 reserved_1;
        aspen_marketdatafeed::info info;
    };

    aspen_marketdatafeed::message_header header = {std::uint16_t(sizeof(aspen_marketdatafeed::message_header) + sizeof(fields_type) - 2), message_type::enum_type::symbol_state_message};

    fields_type fields;

    // parse method
    static symbol_state_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_state_message*>(buffer);
    }

    // parse method const
    static const symbol_state_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_state_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_state_message::fields_type, timestamp) == 0, "unexpected offset of symbol_state_message::fields_type::timestamp");
static_assert(offsetof(symbol_state_message::fields_type, symbol_id) == 8, "unexpected offset of symbol_state_message::fields_type::symbol_id");
static_assert(offsetof(symbol_state_message::fields_type, symbol) == 10, "unexpected offset of symbol_state_message::fields_type::symbol");
static_assert(offsetof(symbol_state_message::fields_type, state) == 21, "unexpected offset of symbol_state_message::fields_type::state");
static_assert(offsetof(symbol_state_message::fields_type, reserved_1) == 22, "unexpected offset of symbol_state_message::fields_type::reserved_1");
static_assert(offsetof(symbol_state_message::fields_type, info) == 23, "unexpected offset of symbol_state_message::fields_type::info");
static_assert(sizeof(symbol_state_message::fields_type) == 27, "unexpected sizeof symbol_state_message::fields_type");
static_assert(sizeof(symbol_state_message) == sizeof(aspen_marketdatafeed::message_header) + 27, "unexpected sizeof symbol_state_message");

#pragma pack(pop)
}
