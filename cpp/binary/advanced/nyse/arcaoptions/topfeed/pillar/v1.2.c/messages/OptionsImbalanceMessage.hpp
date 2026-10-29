#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesSeqNum.hpp"
#include "../types/Reserved4.hpp"
#include "../types/PairedQty.hpp"
#include "../types/TotalImbalanceQty.hpp"
#include "../types/MarketImbalanceQty.hpp"
#include "../types/Reserved2.hpp"
#include "../types/AuctionType.hpp"
#include "../types/ImbalanceSide.hpp"
#include "../types/ContinuousBookClearingPrice.hpp"
#include "../types/AuctionInterestClearingPrice.hpp"
#include "../types/SecondReserved4.hpp"
#include "../types/IndicativeMatchPrice.hpp"
#include "../types/UpperCollar.hpp"
#include "../types/LowerCollar.hpp"
#include "../types/AuctionStatus.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

namespace pillar_topfeed = ::nyse::arcaoptions::topfeed::pillar::v1_2_c;

#pragma pack(push, 1)

// Options Imbalance Message
struct options_imbalance_message {

    struct fields_type {
        pillar_topfeed::source_time source_time;
        pillar_topfeed::source_time_ns source_time_ns;
        pillar_topfeed::series_index series_index;
        pillar_topfeed::series_seq_num series_seq_num;
        pillar_topfeed::reserved_4 reserved_4;
        pillar_topfeed::paired_qty paired_qty;
        pillar_topfeed::total_imbalance_qty total_imbalance_qty;
        pillar_topfeed::market_imbalance_qty market_imbalance_qty;
        pillar_topfeed::reserved_2 reserved_2;
        pillar_topfeed::auction_type auction_type;
        pillar_topfeed::imbalance_side imbalance_side;
        pillar_topfeed::continuous_book_clearing_price continuous_book_clearing_price;
        pillar_topfeed::auction_interest_clearing_price auction_interest_clearing_price;
        pillar_topfeed::second_reserved_4 second_reserved_4;
        pillar_topfeed::indicative_match_price indicative_match_price;
        pillar_topfeed::upper_collar upper_collar;
        pillar_topfeed::lower_collar lower_collar;
        pillar_topfeed::auction_status auction_status;
    };

    pillar_topfeed::message_header header = {std::uint16_t(sizeof(pillar_topfeed::message_header) + sizeof(fields_type)), message_type::enum_type::options_imbalance_message};

    fields_type fields;

    // parse method
    static options_imbalance_message* parse(std::byte* buffer) {
        return reinterpret_cast<options_imbalance_message*>(buffer);
    }

    // parse method const
    static const options_imbalance_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const options_imbalance_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(options_imbalance_message::fields_type, source_time) == 0, "unexpected offset of options_imbalance_message::fields_type::source_time");
static_assert(offsetof(options_imbalance_message::fields_type, source_time_ns) == 4, "unexpected offset of options_imbalance_message::fields_type::source_time_ns");
static_assert(offsetof(options_imbalance_message::fields_type, series_index) == 8, "unexpected offset of options_imbalance_message::fields_type::series_index");
static_assert(offsetof(options_imbalance_message::fields_type, series_seq_num) == 12, "unexpected offset of options_imbalance_message::fields_type::series_seq_num");
static_assert(offsetof(options_imbalance_message::fields_type, reserved_4) == 16, "unexpected offset of options_imbalance_message::fields_type::reserved_4");
static_assert(offsetof(options_imbalance_message::fields_type, paired_qty) == 20, "unexpected offset of options_imbalance_message::fields_type::paired_qty");
static_assert(offsetof(options_imbalance_message::fields_type, total_imbalance_qty) == 24, "unexpected offset of options_imbalance_message::fields_type::total_imbalance_qty");
static_assert(offsetof(options_imbalance_message::fields_type, market_imbalance_qty) == 28, "unexpected offset of options_imbalance_message::fields_type::market_imbalance_qty");
static_assert(offsetof(options_imbalance_message::fields_type, reserved_2) == 32, "unexpected offset of options_imbalance_message::fields_type::reserved_2");
static_assert(offsetof(options_imbalance_message::fields_type, auction_type) == 34, "unexpected offset of options_imbalance_message::fields_type::auction_type");
static_assert(offsetof(options_imbalance_message::fields_type, imbalance_side) == 35, "unexpected offset of options_imbalance_message::fields_type::imbalance_side");
static_assert(offsetof(options_imbalance_message::fields_type, continuous_book_clearing_price) == 36, "unexpected offset of options_imbalance_message::fields_type::continuous_book_clearing_price");
static_assert(offsetof(options_imbalance_message::fields_type, auction_interest_clearing_price) == 40, "unexpected offset of options_imbalance_message::fields_type::auction_interest_clearing_price");
static_assert(offsetof(options_imbalance_message::fields_type, second_reserved_4) == 44, "unexpected offset of options_imbalance_message::fields_type::second_reserved_4");
static_assert(offsetof(options_imbalance_message::fields_type, indicative_match_price) == 48, "unexpected offset of options_imbalance_message::fields_type::indicative_match_price");
static_assert(offsetof(options_imbalance_message::fields_type, upper_collar) == 52, "unexpected offset of options_imbalance_message::fields_type::upper_collar");
static_assert(offsetof(options_imbalance_message::fields_type, lower_collar) == 56, "unexpected offset of options_imbalance_message::fields_type::lower_collar");
static_assert(offsetof(options_imbalance_message::fields_type, auction_status) == 60, "unexpected offset of options_imbalance_message::fields_type::auction_status");
static_assert(sizeof(options_imbalance_message::fields_type) == 61, "unexpected sizeof options_imbalance_message::fields_type");
static_assert(sizeof(options_imbalance_message) == sizeof(pillar_topfeed::message_header) + 61, "unexpected sizeof options_imbalance_message");

#pragma pack(pop)
}
