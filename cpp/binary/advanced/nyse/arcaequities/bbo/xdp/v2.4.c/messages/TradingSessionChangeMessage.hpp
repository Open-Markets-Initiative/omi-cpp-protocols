#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradingSession.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

namespace xdp_bbo = ::nyse::arcaequities::bbo::xdp::v2_4_c;

#pragma pack(push, 1)

// Trading Session Change Message
struct trading_session_change_message {

    struct fields_type {
        xdp_bbo::source_time source_time;
        xdp_bbo::source_time_ns source_time_ns;
        xdp_bbo::symbol_index symbol_index;
        xdp_bbo::symbol_seq_num symbol_seq_num;
        xdp_bbo::trading_session trading_session;
    };

    xdp_bbo::message_header header = {std::uint16_t(sizeof(xdp_bbo::message_header) + sizeof(fields_type)), message_type::enum_type::trading_session_change_message};

    fields_type fields;

    // parse method
    static trading_session_change_message* parse(std::byte* buffer) {
        return reinterpret_cast<trading_session_change_message*>(buffer);
    }

    // parse method const
    static const trading_session_change_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const trading_session_change_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(trading_session_change_message::fields_type, source_time) == 0, "unexpected offset of trading_session_change_message::fields_type::source_time");
static_assert(offsetof(trading_session_change_message::fields_type, source_time_ns) == 4, "unexpected offset of trading_session_change_message::fields_type::source_time_ns");
static_assert(offsetof(trading_session_change_message::fields_type, symbol_index) == 8, "unexpected offset of trading_session_change_message::fields_type::symbol_index");
static_assert(offsetof(trading_session_change_message::fields_type, symbol_seq_num) == 12, "unexpected offset of trading_session_change_message::fields_type::symbol_seq_num");
static_assert(offsetof(trading_session_change_message::fields_type, trading_session) == 16, "unexpected offset of trading_session_change_message::fields_type::trading_session");
static_assert(sizeof(trading_session_change_message::fields_type) == 17, "unexpected sizeof trading_session_change_message::fields_type");
static_assert(sizeof(trading_session_change_message) == sizeof(xdp_bbo::message_header) + 17, "unexpected sizeof trading_session_change_message");

#pragma pack(pop)
}
