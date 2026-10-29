#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PositionChange.hpp"
#include "../types/Side.hpp"
#include "../types/Reserved1.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::texasequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Modify Order Message
struct modify_order_message {

    struct fields_type {
        pillar_integratedfeed::source_time_ns source_time_ns;
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol_seq_num symbol_seq_num;
        pillar_integratedfeed::order_id order_id;
        pillar_integratedfeed::price price;
        pillar_integratedfeed::volume volume;
        pillar_integratedfeed::position_change position_change;
        pillar_integratedfeed::side side;
        pillar_integratedfeed::reserved_1 reserved_1;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::modify_order_message};

    fields_type fields;

    // parse method
    static modify_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<modify_order_message*>(buffer);
    }

    // parse method const
    static const modify_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const modify_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(modify_order_message::fields_type, source_time_ns) == 0, "unexpected offset of modify_order_message::fields_type::source_time_ns");
static_assert(offsetof(modify_order_message::fields_type, symbol_index) == 4, "unexpected offset of modify_order_message::fields_type::symbol_index");
static_assert(offsetof(modify_order_message::fields_type, symbol_seq_num) == 8, "unexpected offset of modify_order_message::fields_type::symbol_seq_num");
static_assert(offsetof(modify_order_message::fields_type, order_id) == 12, "unexpected offset of modify_order_message::fields_type::order_id");
static_assert(offsetof(modify_order_message::fields_type, price) == 20, "unexpected offset of modify_order_message::fields_type::price");
static_assert(offsetof(modify_order_message::fields_type, volume) == 24, "unexpected offset of modify_order_message::fields_type::volume");
static_assert(offsetof(modify_order_message::fields_type, position_change) == 28, "unexpected offset of modify_order_message::fields_type::position_change");
static_assert(offsetof(modify_order_message::fields_type, side) == 29, "unexpected offset of modify_order_message::fields_type::side");
static_assert(offsetof(modify_order_message::fields_type, reserved_1) == 30, "unexpected offset of modify_order_message::fields_type::reserved_1");
static_assert(sizeof(modify_order_message::fields_type) == 31, "unexpected sizeof modify_order_message::fields_type");
static_assert(sizeof(modify_order_message) == sizeof(pillar_integratedfeed::message_header) + 31, "unexpected sizeof modify_order_message");

#pragma pack(pop)
}
