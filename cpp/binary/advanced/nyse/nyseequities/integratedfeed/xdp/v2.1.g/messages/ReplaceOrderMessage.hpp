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
#include "../types/PrevPriceParitySplits.hpp"
#include "../types/NewPriceParitySplits.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

namespace xdp_integratedfeed = ::nyse::nyseequities::integratedfeed::xdp::v2_1_g;

#pragma pack(push, 1)

// Replace Order Message
struct replace_order_message {

    struct fields_type {
        xdp_integratedfeed::source_time_ns source_time_ns;
        xdp_integratedfeed::symbol_index symbol_index;
        xdp_integratedfeed::symbol_seq_num symbol_seq_num;
        xdp_integratedfeed::order_id order_id;
        xdp_integratedfeed::new_order_id new_order_id;
        xdp_integratedfeed::price price;
        xdp_integratedfeed::volume volume;
        xdp_integratedfeed::prev_price_parity_splits prev_price_parity_splits;
        xdp_integratedfeed::new_price_parity_splits new_price_parity_splits;
    };

    xdp_integratedfeed::message_header header = {std::uint16_t(sizeof(xdp_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::replace_order_message};

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
static_assert(offsetof(replace_order_message::fields_type, prev_price_parity_splits) == 36, "unexpected offset of replace_order_message::fields_type::prev_price_parity_splits");
static_assert(offsetof(replace_order_message::fields_type, new_price_parity_splits) == 37, "unexpected offset of replace_order_message::fields_type::new_price_parity_splits");
static_assert(sizeof(replace_order_message::fields_type) == 38, "unexpected sizeof replace_order_message::fields_type");
static_assert(sizeof(replace_order_message) == sizeof(xdp_integratedfeed::message_header) + 38, "unexpected sizeof replace_order_message");

#pragma pack(pop)
}
