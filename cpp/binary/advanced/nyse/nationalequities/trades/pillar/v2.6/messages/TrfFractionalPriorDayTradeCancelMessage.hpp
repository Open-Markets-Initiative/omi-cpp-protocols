#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/FractionalVolume.hpp"
#include "../types/PriorDayTime.hpp"
#include "../types/PriorDayTimeNs.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

namespace pillar_trades = ::nyse::nationalequities::trades::pillar::v2_6;

#pragma pack(push, 1)

// Trf Fractional Prior Day Trade Cancel Message
struct trf_fractional_prior_day_trade_cancel_message {

    struct fields_type {
        pillar_trades::source_time source_time;
        pillar_trades::source_time_ns source_time_ns;
        pillar_trades::symbol_index symbol_index;
        pillar_trades::symbol_seq_num symbol_seq_num;
        pillar_trades::trade_id trade_id;
        pillar_trades::price price;
        pillar_trades::fractional_volume fractional_volume;
        pillar_trades::prior_day_time prior_day_time;
        pillar_trades::prior_day_time_ns prior_day_time_ns;
    };

    pillar_trades::message_header header = {std::uint16_t(sizeof(pillar_trades::message_header) + sizeof(fields_type)), message_type::enum_type::trf_fractional_prior_day_trade_cancel_message};

    fields_type fields;

    // parse method
    static trf_fractional_prior_day_trade_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<trf_fractional_prior_day_trade_cancel_message*>(buffer);
    }

    // parse method const
    static const trf_fractional_prior_day_trade_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trf_fractional_prior_day_trade_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, source_time) == 0, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::source_time");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, source_time_ns) == 4, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::source_time_ns");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, symbol_index) == 8, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::symbol_index");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, symbol_seq_num) == 12, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::symbol_seq_num");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, trade_id) == 16, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::trade_id");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, price) == 20, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::price");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, fractional_volume) == 24, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::fractional_volume");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, prior_day_time) == 32, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::prior_day_time");
static_assert(offsetof(trf_fractional_prior_day_trade_cancel_message::fields_type, prior_day_time_ns) == 36, "unexpected offset of trf_fractional_prior_day_trade_cancel_message::fields_type::prior_day_time_ns");
static_assert(sizeof(trf_fractional_prior_day_trade_cancel_message::fields_type) == 40, "unexpected sizeof trf_fractional_prior_day_trade_cancel_message::fields_type");
static_assert(sizeof(trf_fractional_prior_day_trade_cancel_message) == sizeof(pillar_trades::message_header) + 40, "unexpected sizeof trf_fractional_prior_day_trade_cancel_message");

#pragma pack(pop)
}
