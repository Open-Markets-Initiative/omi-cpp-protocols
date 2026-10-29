#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/OriginalTradeId.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

namespace pillar_trades = ::nyse::nationalequities::trades::pillar::v2_6;

#pragma pack(push, 1)

// Trade Cancel Message
struct trade_cancel_message {

    struct fields_type {
        pillar_trades::source_time source_time;
        pillar_trades::source_time_ns source_time_ns;
        pillar_trades::symbol_index symbol_index;
        pillar_trades::symbol_seq_num symbol_seq_num;
        pillar_trades::original_trade_id original_trade_id;
    };

    pillar_trades::message_header header = {std::uint16_t(sizeof(pillar_trades::message_header) + sizeof(fields_type)), message_type::enum_type::trade_cancel_message};

    fields_type fields;

    // parse method
    static trade_cancel_message* parse(std::byte* buffer) {
        return reinterpret_cast<trade_cancel_message*>(buffer);
    }

    // parse method const
    static const trade_cancel_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trade_cancel_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trade_cancel_message::fields_type, source_time) == 0, "unexpected offset of trade_cancel_message::fields_type::source_time");
static_assert(offsetof(trade_cancel_message::fields_type, source_time_ns) == 4, "unexpected offset of trade_cancel_message::fields_type::source_time_ns");
static_assert(offsetof(trade_cancel_message::fields_type, symbol_index) == 8, "unexpected offset of trade_cancel_message::fields_type::symbol_index");
static_assert(offsetof(trade_cancel_message::fields_type, symbol_seq_num) == 12, "unexpected offset of trade_cancel_message::fields_type::symbol_seq_num");
static_assert(offsetof(trade_cancel_message::fields_type, original_trade_id) == 16, "unexpected offset of trade_cancel_message::fields_type::original_trade_id");
static_assert(sizeof(trade_cancel_message::fields_type) == 20, "unexpected sizeof trade_cancel_message::fields_type");
static_assert(sizeof(trade_cancel_message) == sizeof(pillar_trades::message_header) + 20, "unexpected sizeof trade_cancel_message");

#pragma pack(pop)
}
