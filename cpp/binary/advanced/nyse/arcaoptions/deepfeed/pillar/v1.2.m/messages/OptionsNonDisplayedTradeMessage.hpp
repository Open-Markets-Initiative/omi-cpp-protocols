#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/TradeId.hpp"
#include "../types/Price.hpp"
#include "../types/Volume.hpp"
#include "../types/PrintableFlag.hpp"
#include "../types/NonDisplayedTradeTradeCond1.hpp"
#include "../types/Reserved3.hpp"
#include "../types/PriceType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Options Non Displayed Trade Message
struct options_non_displayed_trade_message {

    struct fields_type {
        pillar_deepfeed::source_time_ns source_time_ns;
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_seq_num series_seq_num;
        pillar_deepfeed::trade_id trade_id;
        pillar_deepfeed::price price;
        pillar_deepfeed::volume volume;
        pillar_deepfeed::printable_flag printable_flag;
        pillar_deepfeed::non_displayed_trade_trade_cond_1 non_displayed_trade_trade_cond_1;
        pillar_deepfeed::reserved_3 reserved_3;
        pillar_deepfeed::price_type price_type;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_non_displayed_trade_message};

    fields_type fields;

    // parse method
    static options_non_displayed_trade_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_non_displayed_trade_message*>(buffer);
    }

    // parse method const
    static const options_non_displayed_trade_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_non_displayed_trade_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_non_displayed_trade_message::fields_type, source_time_ns) == 0, "unexpected offset of options_non_displayed_trade_message::fields_type::source_time_ns");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, series_index) == 4, "unexpected offset of options_non_displayed_trade_message::fields_type::series_index");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, series_seq_num) == 8, "unexpected offset of options_non_displayed_trade_message::fields_type::series_seq_num");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, trade_id) == 12, "unexpected offset of options_non_displayed_trade_message::fields_type::trade_id");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, price) == 16, "unexpected offset of options_non_displayed_trade_message::fields_type::price");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, volume) == 20, "unexpected offset of options_non_displayed_trade_message::fields_type::volume");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, printable_flag) == 24, "unexpected offset of options_non_displayed_trade_message::fields_type::printable_flag");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, non_displayed_trade_trade_cond_1) == 25, "unexpected offset of options_non_displayed_trade_message::fields_type::non_displayed_trade_trade_cond_1");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, reserved_3) == 26, "unexpected offset of options_non_displayed_trade_message::fields_type::reserved_3");
static_assert(offsetof(options_non_displayed_trade_message::fields_type, price_type) == 29, "unexpected offset of options_non_displayed_trade_message::fields_type::price_type");
static_assert(sizeof(options_non_displayed_trade_message::fields_type) == 30, "unexpected sizeof options_non_displayed_trade_message::fields_type");
static_assert(sizeof(options_non_displayed_trade_message) == sizeof(pillar_deepfeed::message_header) + 30, "unexpected sizeof options_non_displayed_trade_message");

#pragma pack(pop)
}
