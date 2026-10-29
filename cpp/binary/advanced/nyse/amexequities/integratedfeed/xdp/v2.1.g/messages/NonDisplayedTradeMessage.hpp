#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/DbExecId.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

namespace xdp_integratedfeed = ::nyse::amexequities::integratedfeed::xdp::v2_1_g;

#pragma pack(push, 1)

// Non Displayed Trade Message
struct non_displayed_trade_message {

    struct fields_type {
        xdp_integratedfeed::source_time_ns source_time_ns;
        xdp_integratedfeed::symbol_index symbol_index;
        xdp_integratedfeed::symbol_seq_num symbol_seq_num;
        xdp_integratedfeed::trade_id trade_id;
        xdp_integratedfeed::price price;
        xdp_integratedfeed::volume volume;
        xdp_integratedfeed::printable_flag printable_flag;
        xdp_integratedfeed::db_exec_id db_exec_id;
    };

    xdp_integratedfeed::message_header header = {std::uint16_t(sizeof(xdp_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::non_displayed_trade_message};

    fields_type fields;

    // parse method
    static non_displayed_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<non_displayed_trade_message*>(buffer);
    }

    // parse method const
    static const non_displayed_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const non_displayed_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(non_displayed_trade_message::fields_type, source_time_ns) == 0, "unexpected offset of non_displayed_trade_message::fields_type::source_time_ns");
static_assert(offsetof(non_displayed_trade_message::fields_type, symbol_index) == 4, "unexpected offset of non_displayed_trade_message::fields_type::symbol_index");
static_assert(offsetof(non_displayed_trade_message::fields_type, symbol_seq_num) == 8, "unexpected offset of non_displayed_trade_message::fields_type::symbol_seq_num");
static_assert(offsetof(non_displayed_trade_message::fields_type, trade_id) == 12, "unexpected offset of non_displayed_trade_message::fields_type::trade_id");
static_assert(offsetof(non_displayed_trade_message::fields_type, price) == 16, "unexpected offset of non_displayed_trade_message::fields_type::price");
static_assert(offsetof(non_displayed_trade_message::fields_type, volume) == 20, "unexpected offset of non_displayed_trade_message::fields_type::volume");
static_assert(offsetof(non_displayed_trade_message::fields_type, printable_flag) == 24, "unexpected offset of non_displayed_trade_message::fields_type::printable_flag");
static_assert(offsetof(non_displayed_trade_message::fields_type, db_exec_id) == 25, "unexpected offset of non_displayed_trade_message::fields_type::db_exec_id");
static_assert(sizeof(non_displayed_trade_message::fields_type) == 29, "unexpected sizeof non_displayed_trade_message::fields_type");
static_assert(sizeof(non_displayed_trade_message) == sizeof(xdp_integratedfeed::message_header) + 29, "unexpected sizeof non_displayed_trade_message");

#pragma pack(pop)
}
