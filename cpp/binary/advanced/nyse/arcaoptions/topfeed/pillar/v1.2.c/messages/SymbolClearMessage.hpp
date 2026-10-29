#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/NextSourceSeqNum.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Symbol Clear Message
struct symbol_clear_message {

    struct fields_type {
        pillar_topfeed::source_time source_time;
        pillar_topfeed::source_time_ns source_time_ns;
        pillar_topfeed::symbol_index symbol_index;
        pillar_topfeed::next_source_seq_num next_source_seq_num;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::symbol_clear_message};

    fields_type fields;

    // parse method
    static symbol_clear_message* parse(std::byte* buffer) {
        return reinterpret_cast<symbol_clear_message*>(buffer);
    }

    // parse method const
    static const symbol_clear_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const symbol_clear_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(symbol_clear_message::fields_type, source_time) == 0, "unexpected offset of symbol_clear_message::fields_type::source_time");
static_assert(offsetof(symbol_clear_message::fields_type, source_time_ns) == 4, "unexpected offset of symbol_clear_message::fields_type::source_time_ns");
static_assert(offsetof(symbol_clear_message::fields_type, symbol_index) == 8, "unexpected offset of symbol_clear_message::fields_type::symbol_index");
static_assert(offsetof(symbol_clear_message::fields_type, next_source_seq_num) == 12, "unexpected offset of symbol_clear_message::fields_type::next_source_seq_num");
static_assert(sizeof(symbol_clear_message::fields_type) == 16, "unexpected sizeof symbol_clear_message::fields_type");
static_assert(sizeof(symbol_clear_message) == sizeof(pillar_topfeed::message_header) + 16, "unexpected sizeof symbol_clear_message");

#pragma pack(pop)
}
