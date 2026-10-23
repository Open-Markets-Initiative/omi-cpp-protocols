#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/Id.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/SourceTime.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

namespace xdp_integratedfeed = ::nyse::nyseequities::integratedfeed::xdp::v2_3_a;

#pragma pack(push, 1)

// Source Time Reference Message
struct source_time_reference_message {

    struct fields_type {
        xdp_integratedfeed::id id;
        xdp_integratedfeed::symbol_seq_num symbol_seq_num;
        xdp_integratedfeed::source_time source_time;
    };

    xdp_integratedfeed::message_header header = {std::uint16_t(sizeof(xdp_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::source_time_reference_message};

    fields_type fields;

    // parse method
    static source_time_reference_message* parse(std::byte* buffer) {
        return reinterpret_cast<source_time_reference_message*>(buffer);
    }

    // parse method const
    static const source_time_reference_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const source_time_reference_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(source_time_reference_message::fields_type, id) == 0, "unexpected offset of source_time_reference_message::fields_type::id");
static_assert(offsetof(source_time_reference_message::fields_type, symbol_seq_num) == 4, "unexpected offset of source_time_reference_message::fields_type::symbol_seq_num");
static_assert(offsetof(source_time_reference_message::fields_type, source_time) == 8, "unexpected offset of source_time_reference_message::fields_type::source_time");
static_assert(sizeof(source_time_reference_message::fields_type) == 12, "unexpected sizeof source_time_reference_message::fields_type");
static_assert(sizeof(source_time_reference_message) == sizeof(xdp_integratedfeed::message_header) + 12, "unexpected sizeof source_time_reference_message");

#pragma pack(pop)
}
