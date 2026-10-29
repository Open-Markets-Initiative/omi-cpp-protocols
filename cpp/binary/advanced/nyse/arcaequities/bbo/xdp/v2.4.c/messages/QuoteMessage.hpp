#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SymbolIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskVolume.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/RpiIndicator.hpp"
#include "../types/Reserved4.hpp"

namespace nyse::arcaequities::bbo::xdp::v2_4_c {

namespace xdp_bbo = ::nyse::arcaequities::bbo::xdp::v2_4_c;

#pragma pack(push, 1)

// Quote Message
struct quote_message {

    struct fields_type {
        xdp_bbo::source_time_ns source_time_ns;
        xdp_bbo::symbol_index symbol_index;
        xdp_bbo::symbol_seq_num symbol_seq_num;
        xdp_bbo::ask_price ask_price;
        xdp_bbo::ask_volume ask_volume;
        xdp_bbo::bid_price bid_price;
        xdp_bbo::bid_volume bid_volume;
        xdp_bbo::quote_condition quote_condition;
        xdp_bbo::rpi_indicator rpi_indicator;
        xdp_bbo::reserved_4 reserved_4;
    };

    xdp_bbo::message_header header = {std::uint16_t(sizeof(xdp_bbo::message_header) + sizeof(fields_type)), message_type::enum_type::quote_message};

    fields_type fields;

    // parse method
    static quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<quote_message*>(buffer);
    }

    // parse method const
    static const quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(quote_message::fields_type, source_time_ns) == 0, "unexpected offset of quote_message::fields_type::source_time_ns");
static_assert(offsetof(quote_message::fields_type, symbol_index) == 4, "unexpected offset of quote_message::fields_type::symbol_index");
static_assert(offsetof(quote_message::fields_type, symbol_seq_num) == 8, "unexpected offset of quote_message::fields_type::symbol_seq_num");
static_assert(offsetof(quote_message::fields_type, ask_price) == 12, "unexpected offset of quote_message::fields_type::ask_price");
static_assert(offsetof(quote_message::fields_type, ask_volume) == 16, "unexpected offset of quote_message::fields_type::ask_volume");
static_assert(offsetof(quote_message::fields_type, bid_price) == 20, "unexpected offset of quote_message::fields_type::bid_price");
static_assert(offsetof(quote_message::fields_type, bid_volume) == 24, "unexpected offset of quote_message::fields_type::bid_volume");
static_assert(offsetof(quote_message::fields_type, quote_condition) == 28, "unexpected offset of quote_message::fields_type::quote_condition");
static_assert(offsetof(quote_message::fields_type, rpi_indicator) == 29, "unexpected offset of quote_message::fields_type::rpi_indicator");
static_assert(offsetof(quote_message::fields_type, reserved_4) == 30, "unexpected offset of quote_message::fields_type::reserved_4");
static_assert(sizeof(quote_message::fields_type) == 34, "unexpected sizeof quote_message::fields_type");
static_assert(sizeof(quote_message) == sizeof(xdp_bbo::message_header) + 34, "unexpected sizeof quote_message");

#pragma pack(pop)
}
