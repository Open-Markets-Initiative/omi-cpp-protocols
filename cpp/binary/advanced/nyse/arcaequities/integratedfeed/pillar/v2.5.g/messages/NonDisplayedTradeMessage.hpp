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
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/TradeCond3.hpp"
#include "../types/TradeCond4.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::arcaequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Non Displayed Trade Message
struct non_displayed_trade_message {

    struct fields_type {
        pillar_integratedfeed::source_time_ns source_time_ns;
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol_seq_num symbol_seq_num;
        pillar_integratedfeed::trade_id trade_id;
        pillar_integratedfeed::price price;
        pillar_integratedfeed::volume volume;
        pillar_integratedfeed::printable_flag printable_flag;
        pillar_integratedfeed::trade_cond_1 trade_cond_1;
        pillar_integratedfeed::trade_cond_2 trade_cond_2;
        pillar_integratedfeed::trade_cond_3 trade_cond_3;
        pillar_integratedfeed::trade_cond_4 trade_cond_4;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::non_displayed_trade_message};

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
static_assert(offsetof(non_displayed_trade_message::fields_type, trade_cond_1) == 25, "unexpected offset of non_displayed_trade_message::fields_type::trade_cond_1");
static_assert(offsetof(non_displayed_trade_message::fields_type, trade_cond_2) == 26, "unexpected offset of non_displayed_trade_message::fields_type::trade_cond_2");
static_assert(offsetof(non_displayed_trade_message::fields_type, trade_cond_3) == 27, "unexpected offset of non_displayed_trade_message::fields_type::trade_cond_3");
static_assert(offsetof(non_displayed_trade_message::fields_type, trade_cond_4) == 28, "unexpected offset of non_displayed_trade_message::fields_type::trade_cond_4");
static_assert(sizeof(non_displayed_trade_message::fields_type) == 29, "unexpected sizeof non_displayed_trade_message::fields_type");
static_assert(sizeof(non_displayed_trade_message) == sizeof(pillar_integratedfeed::message_header) + 29, "unexpected sizeof non_displayed_trade_message");

#pragma pack(pop)
}
