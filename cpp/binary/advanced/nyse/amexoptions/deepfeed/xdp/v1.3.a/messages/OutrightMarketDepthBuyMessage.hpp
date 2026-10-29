#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/FirstLevelPrice.hpp"
#include "../types/SecondLevelPrice.hpp"
#include "../types/ThirdLevelPrice.hpp"
#include "../types/FirstLevelVolume.hpp"
#include "../types/SecondLevelVolume.hpp"
#include "../types/ThirdLevelVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/FirstLevelCustomerVolume.hpp"
#include "../types/SecondLevelCustomerVolume.hpp"
#include "../types/ThirdLevelCustomerVolume.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

namespace xdp_deepfeed = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Outright Market Depth Buy Message
struct outright_market_depth_buy_message {

    struct fields_type {
        xdp_deepfeed::source_time source_time;
        xdp_deepfeed::source_ns source_ns;
        xdp_deepfeed::series_index series_index;
        xdp_deepfeed::symbol_seq_num symbol_seq_num;
        xdp_deepfeed::first_level_price first_level_price;
        xdp_deepfeed::second_level_price second_level_price;
        xdp_deepfeed::third_level_price third_level_price;
        xdp_deepfeed::first_level_volume first_level_volume;
        xdp_deepfeed::second_level_volume second_level_volume;
        xdp_deepfeed::third_level_volume third_level_volume;
        xdp_deepfeed::quote_condition quote_condition;
        xdp_deepfeed::reserved_1 reserved_1;
        xdp_deepfeed::first_level_customer_volume first_level_customer_volume;
        xdp_deepfeed::second_level_customer_volume second_level_customer_volume;
        xdp_deepfeed::third_level_customer_volume third_level_customer_volume;
        xdp_deepfeed::reserved_2 reserved_2;
    };

    xdp_deepfeed::message_header header = {std::uint16_t(sizeof(xdp_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::outright_market_depth_buy_message};

    fields_type fields;

    // parse method
    static outright_market_depth_buy_message* parse(std::byte* buffer) {
        return reinterpret_cast<outright_market_depth_buy_message*>(buffer);
    }

    // parse method const
    static const outright_market_depth_buy_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const outright_market_depth_buy_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(outright_market_depth_buy_message::fields_type, source_time) == 0, "unexpected offset of outright_market_depth_buy_message::fields_type::source_time");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, source_ns) == 4, "unexpected offset of outright_market_depth_buy_message::fields_type::source_ns");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, series_index) == 8, "unexpected offset of outright_market_depth_buy_message::fields_type::series_index");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, symbol_seq_num) == 12, "unexpected offset of outright_market_depth_buy_message::fields_type::symbol_seq_num");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, first_level_price) == 16, "unexpected offset of outright_market_depth_buy_message::fields_type::first_level_price");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, second_level_price) == 20, "unexpected offset of outright_market_depth_buy_message::fields_type::second_level_price");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, third_level_price) == 24, "unexpected offset of outright_market_depth_buy_message::fields_type::third_level_price");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, first_level_volume) == 28, "unexpected offset of outright_market_depth_buy_message::fields_type::first_level_volume");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, second_level_volume) == 30, "unexpected offset of outright_market_depth_buy_message::fields_type::second_level_volume");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, third_level_volume) == 32, "unexpected offset of outright_market_depth_buy_message::fields_type::third_level_volume");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, quote_condition) == 34, "unexpected offset of outright_market_depth_buy_message::fields_type::quote_condition");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, reserved_1) == 35, "unexpected offset of outright_market_depth_buy_message::fields_type::reserved_1");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, first_level_customer_volume) == 36, "unexpected offset of outright_market_depth_buy_message::fields_type::first_level_customer_volume");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, second_level_customer_volume) == 38, "unexpected offset of outright_market_depth_buy_message::fields_type::second_level_customer_volume");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, third_level_customer_volume) == 40, "unexpected offset of outright_market_depth_buy_message::fields_type::third_level_customer_volume");
static_assert(offsetof(outright_market_depth_buy_message::fields_type, reserved_2) == 42, "unexpected offset of outright_market_depth_buy_message::fields_type::reserved_2");
static_assert(sizeof(outright_market_depth_buy_message::fields_type) == 44, "unexpected sizeof outright_market_depth_buy_message::fields_type");
static_assert(sizeof(outright_market_depth_buy_message) == sizeof(xdp_deepfeed::message_header) + 44, "unexpected sizeof outright_market_depth_buy_message");

#pragma pack(pop)
}
