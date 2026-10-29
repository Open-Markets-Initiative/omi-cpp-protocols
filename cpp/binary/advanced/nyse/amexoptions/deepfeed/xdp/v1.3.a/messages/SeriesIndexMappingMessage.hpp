#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/ChannelId.hpp"
#include "../types/ReservedA1.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/ReservedB1.hpp"
#include "../types/StreamId.hpp"
#include "../types/UnderlyingIndex.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/OptionSymbolRoot.hpp"
#include "../types/GroupId.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

namespace xdp_deepfeed = ::nyse::amexoptions::deepfeed::xdp::v1_3_a;

#pragma pack(push, 1)

// Series Index Mapping Message
struct series_index_mapping_message {

    struct fields_type {
        xdp_deepfeed::series_index series_index;
        xdp_deepfeed::channel_id channel_id;
        xdp_deepfeed::reserved_a_1 reserved_a_1;
        xdp_deepfeed::market_id market_id;
        xdp_deepfeed::system_id system_id;
        xdp_deepfeed::reserved_b_1 reserved_b_1;
        xdp_deepfeed::stream_id stream_id;
        xdp_deepfeed::underlying_index underlying_index;
        xdp_deepfeed::contract_multiplier contract_multiplier;
        xdp_deepfeed::maturity_date maturity_date;
        xdp_deepfeed::put_or_call put_or_call;
        xdp_deepfeed::strike_price strike_price;
        xdp_deepfeed::price_scale_code price_scale_code;
        xdp_deepfeed::underlying_symbol underlying_symbol;
        xdp_deepfeed::option_symbol_root option_symbol_root;
        xdp_deepfeed::group_id group_id;
    };

    xdp_deepfeed::message_header header = {std::uint16_t(sizeof(xdp_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::series_index_mapping_message};

    fields_type fields;

    // parse method
    static series_index_mapping_message* parse(std::byte* buffer) {
        return reinterpret_cast<series_index_mapping_message*>(buffer);
    }

    // parse method const
    static const series_index_mapping_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const series_index_mapping_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(series_index_mapping_message::fields_type, series_index) == 0, "unexpected offset of series_index_mapping_message::fields_type::series_index");
static_assert(offsetof(series_index_mapping_message::fields_type, channel_id) == 4, "unexpected offset of series_index_mapping_message::fields_type::channel_id");
static_assert(offsetof(series_index_mapping_message::fields_type, reserved_a_1) == 5, "unexpected offset of series_index_mapping_message::fields_type::reserved_a_1");
static_assert(offsetof(series_index_mapping_message::fields_type, market_id) == 6, "unexpected offset of series_index_mapping_message::fields_type::market_id");
static_assert(offsetof(series_index_mapping_message::fields_type, system_id) == 8, "unexpected offset of series_index_mapping_message::fields_type::system_id");
static_assert(offsetof(series_index_mapping_message::fields_type, reserved_b_1) == 9, "unexpected offset of series_index_mapping_message::fields_type::reserved_b_1");
static_assert(offsetof(series_index_mapping_message::fields_type, stream_id) == 10, "unexpected offset of series_index_mapping_message::fields_type::stream_id");
static_assert(offsetof(series_index_mapping_message::fields_type, underlying_index) == 12, "unexpected offset of series_index_mapping_message::fields_type::underlying_index");
static_assert(offsetof(series_index_mapping_message::fields_type, contract_multiplier) == 16, "unexpected offset of series_index_mapping_message::fields_type::contract_multiplier");
static_assert(offsetof(series_index_mapping_message::fields_type, maturity_date) == 18, "unexpected offset of series_index_mapping_message::fields_type::maturity_date");
static_assert(offsetof(series_index_mapping_message::fields_type, put_or_call) == 24, "unexpected offset of series_index_mapping_message::fields_type::put_or_call");
static_assert(offsetof(series_index_mapping_message::fields_type, strike_price) == 25, "unexpected offset of series_index_mapping_message::fields_type::strike_price");
static_assert(offsetof(series_index_mapping_message::fields_type, price_scale_code) == 35, "unexpected offset of series_index_mapping_message::fields_type::price_scale_code");
static_assert(offsetof(series_index_mapping_message::fields_type, underlying_symbol) == 36, "unexpected offset of series_index_mapping_message::fields_type::underlying_symbol");
static_assert(offsetof(series_index_mapping_message::fields_type, option_symbol_root) == 47, "unexpected offset of series_index_mapping_message::fields_type::option_symbol_root");
static_assert(offsetof(series_index_mapping_message::fields_type, group_id) == 52, "unexpected offset of series_index_mapping_message::fields_type::group_id");
static_assert(sizeof(series_index_mapping_message::fields_type) == 56, "unexpected sizeof series_index_mapping_message::fields_type");
static_assert(sizeof(series_index_mapping_message) == sizeof(xdp_deepfeed::message_header) + 56, "unexpected sizeof series_index_mapping_message");

#pragma pack(pop)
}
