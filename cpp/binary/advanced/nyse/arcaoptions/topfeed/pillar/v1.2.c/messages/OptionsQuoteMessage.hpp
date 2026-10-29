#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/AskPrice.hpp"
#include "../types/AskVolume.hpp"
#include "../types/BidPrice.hpp"
#include "../types/BidVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/AskCustomerVolume.hpp"
#include "../types/BidCustomerVolume.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Options Quote Message
struct options_quote_message {

    struct fields_type {
        pillar_topfeed::source_time_ns source_time_ns;
        pillar_topfeed::series_index series_index;
        pillar_topfeed::series_seq_num series_seq_num;
        pillar_topfeed::ask_price ask_price;
        pillar_topfeed::ask_volume ask_volume;
        pillar_topfeed::bid_price bid_price;
        pillar_topfeed::bid_volume bid_volume;
        pillar_topfeed::quote_condition quote_condition;
        pillar_topfeed::reserved_1 reserved_1;
        pillar_topfeed::ask_customer_volume ask_customer_volume;
        pillar_topfeed::bid_customer_volume bid_customer_volume;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_quote_message};

    fields_type fields;

    // parse method
    static options_quote_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_quote_message*>(buffer);
    }

    // parse method const
    static const options_quote_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_quote_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_quote_message::fields_type, source_time_ns) == 0, "unexpected offset of options_quote_message::fields_type::source_time_ns");
static_assert(offsetof(options_quote_message::fields_type, series_index) == 4, "unexpected offset of options_quote_message::fields_type::series_index");
static_assert(offsetof(options_quote_message::fields_type, series_seq_num) == 8, "unexpected offset of options_quote_message::fields_type::series_seq_num");
static_assert(offsetof(options_quote_message::fields_type, ask_price) == 12, "unexpected offset of options_quote_message::fields_type::ask_price");
static_assert(offsetof(options_quote_message::fields_type, ask_volume) == 16, "unexpected offset of options_quote_message::fields_type::ask_volume");
static_assert(offsetof(options_quote_message::fields_type, bid_price) == 20, "unexpected offset of options_quote_message::fields_type::bid_price");
static_assert(offsetof(options_quote_message::fields_type, bid_volume) == 24, "unexpected offset of options_quote_message::fields_type::bid_volume");
static_assert(offsetof(options_quote_message::fields_type, quote_condition) == 28, "unexpected offset of options_quote_message::fields_type::quote_condition");
static_assert(offsetof(options_quote_message::fields_type, reserved_1) == 29, "unexpected offset of options_quote_message::fields_type::reserved_1");
static_assert(offsetof(options_quote_message::fields_type, ask_customer_volume) == 30, "unexpected offset of options_quote_message::fields_type::ask_customer_volume");
static_assert(offsetof(options_quote_message::fields_type, bid_customer_volume) == 34, "unexpected offset of options_quote_message::fields_type::bid_customer_volume");
static_assert(sizeof(options_quote_message::fields_type) == 38, "unexpected sizeof options_quote_message::fields_type");
static_assert(sizeof(options_quote_message) == sizeof(pillar_topfeed::message_header) + 38, "unexpected sizeof options_quote_message");

#pragma pack(pop)
}
