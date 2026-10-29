#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OriginalTradeId.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/FractionalVolume.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/TradeCond3.hpp"
#include "../types/TradeCond4.hpp"
#include "../types/ExecDayTime.hpp"
#include "../types/ExecDayTimeNs.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

namespace pillar_trades = ::nyse::nationalequities::trades::pillar::v2_6;

#pragma pack(push, 1)

// Trf Fractional Trade Correction Message
struct trf_fractional_trade_correction_message {

    struct fields_type {
        pillar_trades::source_time source_time;
        pillar_trades::source_time_ns source_time_ns;
        pillar_trades::symbol_index symbol_index;
        pillar_trades::symbol_seq_num symbol_seq_num;
        pillar_trades::original_trade_id original_trade_id;
        pillar_trades::trade_id trade_id;
        pillar_trades::price price;
        pillar_trades::fractional_volume fractional_volume;
        pillar_trades::trade_cond_1 trade_cond_1;
        pillar_trades::trade_cond_2 trade_cond_2;
        pillar_trades::trade_cond_3 trade_cond_3;
        pillar_trades::trade_cond_4 trade_cond_4;
        pillar_trades::exec_day_time exec_day_time;
        pillar_trades::exec_day_time_ns exec_day_time_ns;
    };

    pillar_trades::message_header header = {std::uint16_t(sizeof(pillar_trades::message_header) + sizeof(fields_type)), message_type::enum_type::trf_fractional_trade_correction_message};

    fields_type fields;

    // parse method
    static trf_fractional_trade_correction_message* parse(std::byte* buffer) {
        return reinterpret_cast<trf_fractional_trade_correction_message*>(buffer);
    }

    // parse method const
    static const trf_fractional_trade_correction_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trf_fractional_trade_correction_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, source_time) == 0, "unexpected offset of trf_fractional_trade_correction_message::fields_type::source_time");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, source_time_ns) == 4, "unexpected offset of trf_fractional_trade_correction_message::fields_type::source_time_ns");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, symbol_index) == 8, "unexpected offset of trf_fractional_trade_correction_message::fields_type::symbol_index");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, symbol_seq_num) == 12, "unexpected offset of trf_fractional_trade_correction_message::fields_type::symbol_seq_num");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, original_trade_id) == 16, "unexpected offset of trf_fractional_trade_correction_message::fields_type::original_trade_id");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, trade_id) == 20, "unexpected offset of trf_fractional_trade_correction_message::fields_type::trade_id");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, price) == 24, "unexpected offset of trf_fractional_trade_correction_message::fields_type::price");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, fractional_volume) == 28, "unexpected offset of trf_fractional_trade_correction_message::fields_type::fractional_volume");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, trade_cond_1) == 36, "unexpected offset of trf_fractional_trade_correction_message::fields_type::trade_cond_1");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, trade_cond_2) == 37, "unexpected offset of trf_fractional_trade_correction_message::fields_type::trade_cond_2");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, trade_cond_3) == 38, "unexpected offset of trf_fractional_trade_correction_message::fields_type::trade_cond_3");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, trade_cond_4) == 39, "unexpected offset of trf_fractional_trade_correction_message::fields_type::trade_cond_4");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, exec_day_time) == 40, "unexpected offset of trf_fractional_trade_correction_message::fields_type::exec_day_time");
static_assert(offsetof(trf_fractional_trade_correction_message::fields_type, exec_day_time_ns) == 44, "unexpected offset of trf_fractional_trade_correction_message::fields_type::exec_day_time_ns");
static_assert(sizeof(trf_fractional_trade_correction_message::fields_type) == 48, "unexpected sizeof trf_fractional_trade_correction_message::fields_type");
static_assert(sizeof(trf_fractional_trade_correction_message) == sizeof(pillar_trades::message_header) + 48, "unexpected sizeof trf_fractional_trade_correction_message");

#pragma pack(pop)
}
