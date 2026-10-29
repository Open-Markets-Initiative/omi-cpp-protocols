#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SourceTime.hpp"
#include "../types/SourceTimeNs.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SymbolSeqNum.hpp"
#include "../types/FirstLevelPrice.hpp"
#include "../types/SecondLevelPrice.hpp"
#include "../types/ThirdLevelPrice.hpp"
#include "../types/FirstVolume.hpp"
#include "../types/SecondVolume.hpp"
#include "../types/ThirdVolume.hpp"
#include "../types/QuoteCondition.hpp"
#include "../types/Reserved1.hpp"
#include "../types/FirstLevelCustomerVolume.hpp"
#include "../types/SecondLevelCustomerVolume.hpp"
#include "../types/ThirdLevelCustomerVolume.hpp"
#include "../types/Reserved2.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

namespace xdp_deepfeed = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Refresh Outright Market Depth Sell Message
struct refresh_outright_market_depth_sell_message {

    struct fields_type {
        xdp_deepfeed::source_time source_time;
        xdp_deepfeed::source_time_ns source_time_ns;
        xdp_deepfeed::series_index series_index;
        xdp_deepfeed::symbol_seq_num symbol_seq_num;
        xdp_deepfeed::first_level_price first_level_price;
        xdp_deepfeed::second_level_price second_level_price;
        xdp_deepfeed::third_level_price third_level_price;
        xdp_deepfeed::first_volume first_volume;
        xdp_deepfeed::second_volume second_volume;
        xdp_deepfeed::third_volume third_volume;
        xdp_deepfeed::quote_condition quote_condition;
        xdp_deepfeed::reserved_1 reserved_1;
        xdp_deepfeed::first_level_customer_volume first_level_customer_volume;
        xdp_deepfeed::second_level_customer_volume second_level_customer_volume;
        xdp_deepfeed::third_level_customer_volume third_level_customer_volume;
        xdp_deepfeed::reserved_2 reserved_2;
    };

    xdp_deepfeed::message_header header = {std::uint16_t(sizeof(xdp_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::refresh_outright_market_depth_sell_message};

    fields_type fields;

    // parse method
    static refresh_outright_market_depth_sell_message* parse(std::byte* buffer) {
        return reinterpret_cast<refresh_outright_market_depth_sell_message*>(buffer);
    }

    // parse method const
    static const refresh_outright_market_depth_sell_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const refresh_outright_market_depth_sell_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, source_time) == 0, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::source_time");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, source_time_ns) == 4, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::source_time_ns");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, series_index) == 8, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::series_index");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, symbol_seq_num) == 12, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::symbol_seq_num");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, first_level_price) == 16, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::first_level_price");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, second_level_price) == 20, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::second_level_price");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, third_level_price) == 24, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::third_level_price");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, first_volume) == 28, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::first_volume");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, second_volume) == 30, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::second_volume");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, third_volume) == 32, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::third_volume");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, quote_condition) == 34, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::quote_condition");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, reserved_1) == 35, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::reserved_1");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, first_level_customer_volume) == 36, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::first_level_customer_volume");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, second_level_customer_volume) == 38, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::second_level_customer_volume");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, third_level_customer_volume) == 40, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::third_level_customer_volume");
static_assert(offsetof(refresh_outright_market_depth_sell_message::fields_type, reserved_2) == 42, "unexpected offset of refresh_outright_market_depth_sell_message::fields_type::reserved_2");
static_assert(sizeof(refresh_outright_market_depth_sell_message::fields_type) == 44, "unexpected sizeof refresh_outright_market_depth_sell_message::fields_type");
static_assert(sizeof(refresh_outright_market_depth_sell_message) == sizeof(xdp_deepfeed::message_header) + 44, "unexpected sizeof refresh_outright_market_depth_sell_message");

#pragma pack(pop)
}
