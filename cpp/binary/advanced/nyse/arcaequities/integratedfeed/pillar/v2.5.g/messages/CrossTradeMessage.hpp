#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/CrossId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/CrossType.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::arcaequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Cross Trade Message
struct cross_trade_message {

    struct fields_type {
        pillar_integratedfeed::source_time_ns source_time_ns;
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol_seq_num symbol_seq_num;
        pillar_integratedfeed::cross_id cross_id;
        pillar_integratedfeed::price price;
        pillar_integratedfeed::volume volume;
        pillar_integratedfeed::cross_type cross_type;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::cross_trade_message};

    fields_type fields;

    // parse method
    static cross_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<cross_trade_message*>(buffer);
    }

    // parse method const
    static const cross_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const cross_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(cross_trade_message::fields_type, source_time_ns) == 0, "unexpected offset of cross_trade_message::fields_type::source_time_ns");
static_assert(offsetof(cross_trade_message::fields_type, symbol_index) == 4, "unexpected offset of cross_trade_message::fields_type::symbol_index");
static_assert(offsetof(cross_trade_message::fields_type, symbol_seq_num) == 8, "unexpected offset of cross_trade_message::fields_type::symbol_seq_num");
static_assert(offsetof(cross_trade_message::fields_type, cross_id) == 12, "unexpected offset of cross_trade_message::fields_type::cross_id");
static_assert(offsetof(cross_trade_message::fields_type, price) == 16, "unexpected offset of cross_trade_message::fields_type::price");
static_assert(offsetof(cross_trade_message::fields_type, volume) == 20, "unexpected offset of cross_trade_message::fields_type::volume");
static_assert(offsetof(cross_trade_message::fields_type, cross_type) == 24, "unexpected offset of cross_trade_message::fields_type::cross_type");
static_assert(sizeof(cross_trade_message::fields_type) == 25, "unexpected sizeof cross_trade_message::fields_type");
static_assert(sizeof(cross_trade_message) == sizeof(pillar_integratedfeed::message_header) + 25, "unexpected sizeof cross_trade_message");

#pragma pack(pop)
}
