#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/CrossId.hpp"
#include "../types/Volume.hpp"

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::amexequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Cross Correction Message
struct cross_correction_message {

    struct fields_type {
        pillar_integratedfeed::source_time_ns source_time_ns;
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol_seq_num symbol_seq_num;
        pillar_integratedfeed::cross_id cross_id;
        pillar_integratedfeed::volume volume;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::cross_correction_message};

    fields_type fields;

    // parse method
    static cross_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<cross_correction_message*>(buffer);
    }

    // parse method const
    static const cross_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const cross_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(cross_correction_message::fields_type, source_time_ns) == 0, "unexpected offset of cross_correction_message::fields_type::source_time_ns");
static_assert(offsetof(cross_correction_message::fields_type, symbol_index) == 4, "unexpected offset of cross_correction_message::fields_type::symbol_index");
static_assert(offsetof(cross_correction_message::fields_type, symbol_seq_num) == 8, "unexpected offset of cross_correction_message::fields_type::symbol_seq_num");
static_assert(offsetof(cross_correction_message::fields_type, cross_id) == 12, "unexpected offset of cross_correction_message::fields_type::cross_id");
static_assert(offsetof(cross_correction_message::fields_type, volume) == 16, "unexpected offset of cross_correction_message::fields_type::volume");
static_assert(sizeof(cross_correction_message::fields_type) == 20, "unexpected sizeof cross_correction_message::fields_type");
static_assert(sizeof(cross_correction_message) == sizeof(pillar_integratedfeed::message_header) + 20, "unexpected sizeof cross_correction_message");

#pragma pack(pop)
}
