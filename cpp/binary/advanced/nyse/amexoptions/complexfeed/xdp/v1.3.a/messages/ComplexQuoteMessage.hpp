#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/ComplexIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/AskPrice.hpp"
#include "../types/BidPrice.hpp"
#include "../types/AskVolume.hpp"
#include "../types/BidVolume.hpp"
#include "../types/AskCustomerVolume.hpp"
#include "../types/BidCustomerVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

namespace xdp_complexfeed = ::nyse::amexoptions::complexfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Complex Quote Message
struct complex_quote_message {

    struct fields_type {
        xdp_complexfeed::source_time source_time;
        xdp_complexfeed::source_time_ns source_time_ns;
        xdp_complexfeed::complex_index complex_index;
        xdp_complexfeed::symbol_seq_num symbol_seq_num;
        xdp_complexfeed::ask_price ask_price;
        xdp_complexfeed::bid_price bid_price;
        xdp_complexfeed::ask_volume ask_volume;
        xdp_complexfeed::bid_volume bid_volume;
        xdp_complexfeed::ask_customer_volume ask_customer_volume;
        xdp_complexfeed::bid_customer_volume bid_customer_volume;
        xdp_complexfeed::quote_condition quote_condition;
        xdp_complexfeed::reserved_1 reserved_1;
        xdp_complexfeed::reserved_2 reserved_2;
    };

    xdp_complexfeed::message_header header = {std::uint16_t(sizeof(xdp_complexfeed::message_header) + sizeof(fields_type)), message_type::enum_type::complex_quote_message};

    fields_type fields;

    // parse method
    static complex_quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_quote_message*>(buffer);
    }

    // parse method const
    static const complex_quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_quote_message::fields_type, source_time) == 0, "unexpected offset of complex_quote_message::fields_type::source_time");
static_assert(offsetof(complex_quote_message::fields_type, source_time_ns) == 4, "unexpected offset of complex_quote_message::fields_type::source_time_ns");
static_assert(offsetof(complex_quote_message::fields_type, complex_index) == 8, "unexpected offset of complex_quote_message::fields_type::complex_index");
static_assert(offsetof(complex_quote_message::fields_type, symbol_seq_num) == 12, "unexpected offset of complex_quote_message::fields_type::symbol_seq_num");
static_assert(offsetof(complex_quote_message::fields_type, ask_price) == 16, "unexpected offset of complex_quote_message::fields_type::ask_price");
static_assert(offsetof(complex_quote_message::fields_type, bid_price) == 20, "unexpected offset of complex_quote_message::fields_type::bid_price");
static_assert(offsetof(complex_quote_message::fields_type, ask_volume) == 24, "unexpected offset of complex_quote_message::fields_type::ask_volume");
static_assert(offsetof(complex_quote_message::fields_type, bid_volume) == 26, "unexpected offset of complex_quote_message::fields_type::bid_volume");
static_assert(offsetof(complex_quote_message::fields_type, ask_customer_volume) == 28, "unexpected offset of complex_quote_message::fields_type::ask_customer_volume");
static_assert(offsetof(complex_quote_message::fields_type, bid_customer_volume) == 30, "unexpected offset of complex_quote_message::fields_type::bid_customer_volume");
static_assert(offsetof(complex_quote_message::fields_type, quote_condition) == 32, "unexpected offset of complex_quote_message::fields_type::quote_condition");
static_assert(offsetof(complex_quote_message::fields_type, reserved_1) == 33, "unexpected offset of complex_quote_message::fields_type::reserved_1");
static_assert(offsetof(complex_quote_message::fields_type, reserved_2) == 34, "unexpected offset of complex_quote_message::fields_type::reserved_2");
static_assert(sizeof(complex_quote_message::fields_type) == 36, "unexpected sizeof complex_quote_message::fields_type");
static_assert(sizeof(complex_quote_message) == sizeof(xdp_complexfeed::message_header) + 36, "unexpected sizeof complex_quote_message");

#pragma pack(pop)
}
