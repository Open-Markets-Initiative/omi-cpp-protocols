#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume4.hpp"
#include "../types/TradeCond1.hpp"
#include "../types/TradeCond2.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Complex Trade Message
struct complex_trade_message {

    struct fields_type {
        xdp_complexfeed::source_time source_time;
        xdp_complexfeed::source_time_ns source_time_ns;
        xdp_complexfeed::complex_index complex_index;
        xdp_complexfeed::symbol_seq_num symbol_seq_num;
        xdp_complexfeed::trade_id trade_id;
        xdp_complexfeed::price price;
        xdp_complexfeed::volume_4 volume_4;
        xdp_complexfeed::trade_cond_1 trade_cond_1;
        xdp_complexfeed::trade_cond_2 trade_cond_2;
        xdp_complexfeed::reserved_2 reserved_2;
    };

    xdp_complexfeed::message_header header = {std::uint16_t(sizeof(xdp_complexfeed::message_header) + sizeof(fields_type)), message_type::enum_type::complex_trade_message};

    fields_type fields;

    // parse method
    static complex_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_trade_message*>(buffer);
    }

    // parse method const
    static const complex_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_trade_message::fields_type, source_time) == 0, "unexpected offset of complex_trade_message::fields_type::source_time");
static_assert(offsetof(complex_trade_message::fields_type, source_time_ns) == 4, "unexpected offset of complex_trade_message::fields_type::source_time_ns");
static_assert(offsetof(complex_trade_message::fields_type, complex_index) == 8, "unexpected offset of complex_trade_message::fields_type::complex_index");
static_assert(offsetof(complex_trade_message::fields_type, symbol_seq_num) == 12, "unexpected offset of complex_trade_message::fields_type::symbol_seq_num");
static_assert(offsetof(complex_trade_message::fields_type, trade_id) == 16, "unexpected offset of complex_trade_message::fields_type::trade_id");
static_assert(offsetof(complex_trade_message::fields_type, price) == 20, "unexpected offset of complex_trade_message::fields_type::price");
static_assert(offsetof(complex_trade_message::fields_type, volume_4) == 24, "unexpected offset of complex_trade_message::fields_type::volume_4");
static_assert(offsetof(complex_trade_message::fields_type, trade_cond_1) == 28, "unexpected offset of complex_trade_message::fields_type::trade_cond_1");
static_assert(offsetof(complex_trade_message::fields_type, trade_cond_2) == 29, "unexpected offset of complex_trade_message::fields_type::trade_cond_2");
static_assert(offsetof(complex_trade_message::fields_type, reserved_2) == 30, "unexpected offset of complex_trade_message::fields_type::reserved_2");
static_assert(sizeof(complex_trade_message::fields_type) == 32, "unexpected sizeof complex_trade_message::fields_type");
static_assert(sizeof(complex_trade_message) == sizeof(xdp_complexfeed::message_header) + 32, "unexpected sizeof complex_trade_message");

#pragma pack(pop)
}
