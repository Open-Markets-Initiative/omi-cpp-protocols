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

namespace nyse::nyseequities::bbo::pillar::v2_5_b {

namespace pillar_bbo = ::nyse::nyseequities::bbo::pillar::v2_5_b;

#pragma pack(push, 1)

// Quote Message
struct quote_message {

    struct fields_type {
        pillar_bbo::source_time_ns source_time_ns;
        pillar_bbo::symbol_index symbol_index;
        pillar_bbo::symbol_seq_num symbol_seq_num;
        pillar_bbo::ask_price ask_price;
        pillar_bbo::ask_volume ask_volume;
        pillar_bbo::bid_price bid_price;
        pillar_bbo::bid_volume bid_volume;
        pillar_bbo::quote_condition quote_condition;
        pillar_bbo::rpi_indicator rpi_indicator;
    };

    pillar_bbo::message_header header = {std::uint16_t(sizeof(pillar_bbo::message_header) + sizeof(fields_type)), message_type::enum_type::quote_message};

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
static_assert(sizeof(quote_message::fields_type) == 30, "unexpected sizeof quote_message::fields_type");
static_assert(sizeof(quote_message) == sizeof(pillar_bbo::message_header) + 30, "unexpected sizeof quote_message");

#pragma pack(pop)
}
