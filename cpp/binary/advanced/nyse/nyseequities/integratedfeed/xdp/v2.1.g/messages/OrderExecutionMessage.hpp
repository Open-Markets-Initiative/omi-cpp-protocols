#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OrderId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/NumParitySplits.hpp"
#include "../types/DbExecId.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

namespace xdp_integratedfeed = ::nyse::nyseequities::integratedfeed::xdp::v2_1_g;

#pragma pack(push, 1)

// Order Execution Message
struct order_execution_message {

    struct fields_type {
        xdp_integratedfeed::source_time_ns source_time_ns;
        xdp_integratedfeed::symbol_index symbol_index;
        xdp_integratedfeed::symbol_seq_num symbol_seq_num;
        xdp_integratedfeed::order_id order_id;
        xdp_integratedfeed::trade_id trade_id;
        xdp_integratedfeed::price price;
        xdp_integratedfeed::volume volume;
        xdp_integratedfeed::printable_flag printable_flag;
        xdp_integratedfeed::num_parity_splits num_parity_splits;
        xdp_integratedfeed::db_exec_id db_exec_id;
    };

    xdp_integratedfeed::message_header header = {std::uint16_t(sizeof(xdp_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::order_execution_message};

    fields_type fields;

    // parse method
    static order_execution_message* parse(std::byte* buffer) {
        return reinterpret_cast<order_execution_message*>(buffer);
    }

    // parse method const
    static const order_execution_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const order_execution_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(order_execution_message::fields_type, source_time_ns) == 0, "unexpected offset of order_execution_message::fields_type::source_time_ns");
static_assert(offsetof(order_execution_message::fields_type, symbol_index) == 4, "unexpected offset of order_execution_message::fields_type::symbol_index");
static_assert(offsetof(order_execution_message::fields_type, symbol_seq_num) == 8, "unexpected offset of order_execution_message::fields_type::symbol_seq_num");
static_assert(offsetof(order_execution_message::fields_type, order_id) == 12, "unexpected offset of order_execution_message::fields_type::order_id");
static_assert(offsetof(order_execution_message::fields_type, trade_id) == 20, "unexpected offset of order_execution_message::fields_type::trade_id");
static_assert(offsetof(order_execution_message::fields_type, price) == 24, "unexpected offset of order_execution_message::fields_type::price");
static_assert(offsetof(order_execution_message::fields_type, volume) == 28, "unexpected offset of order_execution_message::fields_type::volume");
static_assert(offsetof(order_execution_message::fields_type, printable_flag) == 32, "unexpected offset of order_execution_message::fields_type::printable_flag");
static_assert(offsetof(order_execution_message::fields_type, num_parity_splits) == 33, "unexpected offset of order_execution_message::fields_type::num_parity_splits");
static_assert(offsetof(order_execution_message::fields_type, db_exec_id) == 34, "unexpected offset of order_execution_message::fields_type::db_exec_id");
static_assert(sizeof(order_execution_message::fields_type) == 38, "unexpected sizeof order_execution_message::fields_type");
static_assert(sizeof(order_execution_message) == sizeof(xdp_integratedfeed::message_header) + 38, "unexpected sizeof order_execution_message");

#pragma pack(pop)
}
