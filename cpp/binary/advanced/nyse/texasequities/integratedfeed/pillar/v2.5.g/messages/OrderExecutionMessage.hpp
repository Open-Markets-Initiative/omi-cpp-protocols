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
#include "../types/Reserved1.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/TradeCond3.hpp"
#include "../types/TradeCond4.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::texasequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Order Execution Message
struct order_execution_message {

    struct fields_type {
        pillar_integratedfeed::source_time_ns source_time_ns;
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol_seq_num symbol_seq_num;
        pillar_integratedfeed::order_id order_id;
        pillar_integratedfeed::trade_id trade_id;
        pillar_integratedfeed::price price;
        pillar_integratedfeed::volume volume;
        pillar_integratedfeed::printable_flag printable_flag;
        pillar_integratedfeed::reserved_1 reserved_1;
        pillar_integratedfeed::trade_cond_1 trade_cond_1;
        pillar_integratedfeed::trade_cond_2 trade_cond_2;
        pillar_integratedfeed::trade_cond_3 trade_cond_3;
        pillar_integratedfeed::trade_cond_4 trade_cond_4;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::order_execution_message};

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
static_assert(offsetof(order_execution_message::fields_type, reserved_1) == 33, "unexpected offset of order_execution_message::fields_type::reserved_1");
static_assert(offsetof(order_execution_message::fields_type, trade_cond_1) == 34, "unexpected offset of order_execution_message::fields_type::trade_cond_1");
static_assert(offsetof(order_execution_message::fields_type, trade_cond_2) == 35, "unexpected offset of order_execution_message::fields_type::trade_cond_2");
static_assert(offsetof(order_execution_message::fields_type, trade_cond_3) == 36, "unexpected offset of order_execution_message::fields_type::trade_cond_3");
static_assert(offsetof(order_execution_message::fields_type, trade_cond_4) == 37, "unexpected offset of order_execution_message::fields_type::trade_cond_4");
static_assert(sizeof(order_execution_message::fields_type) == 38, "unexpected sizeof order_execution_message::fields_type");
static_assert(sizeof(order_execution_message) == sizeof(pillar_integratedfeed::message_header) + 38, "unexpected sizeof order_execution_message");

#pragma pack(pop)
}
