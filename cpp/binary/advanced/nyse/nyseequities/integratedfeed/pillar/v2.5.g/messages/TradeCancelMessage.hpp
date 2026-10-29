#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

namespace pillar_integratedfeed = ::nyse::nyseequities::integratedfeed::pillar::v2_5_g;

#pragma pack(push, 1)

// Trade Cancel Message
struct trade_cancel_message {

    struct fields_type {
        pillar_integratedfeed::source_time_ns source_time_ns;
        pillar_integratedfeed::symbol_index symbol_index;
        pillar_integratedfeed::symbol_seq_num symbol_seq_num;
        pillar_integratedfeed::trade_id trade_id;
    };

    pillar_integratedfeed::message_header header = {std::uint16_t(sizeof(pillar_integratedfeed::message_header) + sizeof(fields_type)), message_type::enum_type::trade_cancel_message};

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
static_assert(offsetof(trade_cancel_message::fields_type, source_time_ns) == 0, "unexpected offset of trade_cancel_message::fields_type::source_time_ns");
static_assert(offsetof(trade_cancel_message::fields_type, symbol_index) == 4, "unexpected offset of trade_cancel_message::fields_type::symbol_index");
static_assert(offsetof(trade_cancel_message::fields_type, symbol_seq_num) == 8, "unexpected offset of trade_cancel_message::fields_type::symbol_seq_num");
static_assert(offsetof(trade_cancel_message::fields_type, trade_id) == 12, "unexpected offset of trade_cancel_message::fields_type::trade_id");
static_assert(sizeof(trade_cancel_message::fields_type) == 16, "unexpected sizeof trade_cancel_message::fields_type");
static_assert(sizeof(trade_cancel_message) == sizeof(pillar_integratedfeed::message_header) + 16, "unexpected sizeof trade_cancel_message");

#pragma pack(pop)
}
