#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/NewOrderId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/Side.hpp"
#include "../types/Reserved1.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

namespace pillar_integratedfeedretransmission = ::nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g;

#pragma pack(push, 1)

// Replace Order Message
struct replace_order_message {

    struct fields_type {
        pillar_integratedfeedretransmission::source_time_ns source_time_ns;
        pillar_integratedfeedretransmission::symbol_index symbol_index;
        pillar_integratedfeedretransmission::symbol_seq_num symbol_seq_num;
        pillar_integratedfeedretransmission::order_id order_id;
        pillar_integratedfeedretransmission::new_order_id new_order_id;
        pillar_integratedfeedretransmission::price price;
        pillar_integratedfeedretransmission::volume volume;
        pillar_integratedfeedretransmission::side side;
        pillar_integratedfeedretransmission::reserved_1 reserved_1;
    };

    pillar_integratedfeedretransmission::message_header header = {std::uint16_t(sizeof(pillar_integratedfeedretransmission::message_header) + sizeof(fields_type)), message_type::enum_type::replace_order_message};

    fields_type fields;

    // parse method
    static replace_order_message* parse(std::byte* buffer) {
        return reinterpret_cast<replace_order_message*>(buffer);
    }

    // parse method const
    static const replace_order_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const replace_order_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(replace_order_message::fields_type, source_time_ns) == 0, "unexpected offset of replace_order_message::fields_type::source_time_ns");
static_assert(offsetof(replace_order_message::fields_type, symbol_index) == 4, "unexpected offset of replace_order_message::fields_type::symbol_index");
static_assert(offsetof(replace_order_message::fields_type, symbol_seq_num) == 8, "unexpected offset of replace_order_message::fields_type::symbol_seq_num");
static_assert(offsetof(replace_order_message::fields_type, order_id) == 12, "unexpected offset of replace_order_message::fields_type::order_id");
static_assert(offsetof(replace_order_message::fields_type, new_order_id) == 20, "unexpected offset of replace_order_message::fields_type::new_order_id");
static_assert(offsetof(replace_order_message::fields_type, price) == 28, "unexpected offset of replace_order_message::fields_type::price");
static_assert(offsetof(replace_order_message::fields_type, volume) == 32, "unexpected offset of replace_order_message::fields_type::volume");
static_assert(offsetof(replace_order_message::fields_type, side) == 36, "unexpected offset of replace_order_message::fields_type::side");
static_assert(offsetof(replace_order_message::fields_type, reserved_1) == 37, "unexpected offset of replace_order_message::fields_type::reserved_1");
static_assert(sizeof(replace_order_message::fields_type) == 38, "unexpected sizeof replace_order_message::fields_type");
static_assert(sizeof(replace_order_message) == sizeof(pillar_integratedfeedretransmission::message_header) + 38, "unexpected sizeof replace_order_message");

#pragma pack(pop)
}
