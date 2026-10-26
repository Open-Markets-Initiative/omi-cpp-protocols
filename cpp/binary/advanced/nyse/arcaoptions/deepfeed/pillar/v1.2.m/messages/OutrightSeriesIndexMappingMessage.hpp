#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../types/SeriesIndex.hpp"
#include "../types/SeriesType.hpp"
#include "../types/MarketId.hpp"
#include "../types/SystemId.hpp"
#include "../types/OptionSymbolRoot.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/UnderlyingIndex.hpp"
#include "../types/PriceScaleCode.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/ClosingOnlyIndicator.hpp"
#include "../types/Reserved1.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

namespace pillar_deepfeed = ::nyse::arcaoptions::deepfeed::pillar::v1_2_m;

#pragma pack(push, 1)

// Outright Series Index Mapping Message
struct outright_series_index_mapping_message {

    struct fields_type {
        pillar_deepfeed::series_index series_index;
        pillar_deepfeed::series_type series_type;
        pillar_deepfeed::market_id market_id;
        pillar_deepfeed::system_id system_id;
        pillar_deepfeed::option_symbol_root option_symbol_root;
        pillar_deepfeed::underlying_symbol underlying_symbol;
        pillar_deepfeed::underlying_index underlying_index;
        pillar_deepfeed::price_scale_code price_scale_code;
        pillar_deepfeed::contract_multiplier contract_multiplier;
        pillar_deepfeed::maturity_date maturity_date;
        pillar_deepfeed::put_or_call put_or_call;
        pillar_deepfeed::strike_price strike_price;
        pillar_deepfeed::closing_only_indicator closing_only_indicator;
        pillar_deepfeed::reserved_1 reserved_1;
    };

    pillar_deepfeed::message_header header = {std::uint16_t(sizeof(pillar_deepfeed::message_header) + sizeof(fields_type)), message_type::enum_type::outright_series_index_mapping_message};

    fields_type fields;

    // parse method
    static outright_series_index_mapping_message* parse(std::byte* buffer) {
        return reinterpret_cast<outright_series_index_mapping_message*>(buffer);
    }

    // parse method const
    static const outright_series_index_mapping_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const outright_series_index_mapping_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(outright_series_index_mapping_message::fields_type, series_index) == 0, "unexpected offset of outright_series_index_mapping_message::fields_type::series_index");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, series_type) == 4, "unexpected offset of outright_series_index_mapping_message::fields_type::series_type");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, market_id) == 5, "unexpected offset of outright_series_index_mapping_message::fields_type::market_id");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, system_id) == 7, "unexpected offset of outright_series_index_mapping_message::fields_type::system_id");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, option_symbol_root) == 8, "unexpected offset of outright_series_index_mapping_message::fields_type::option_symbol_root");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, underlying_symbol) == 14, "unexpected offset of outright_series_index_mapping_message::fields_type::underlying_symbol");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, underlying_index) == 25, "unexpected offset of outright_series_index_mapping_message::fields_type::underlying_index");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, price_scale_code) == 29, "unexpected offset of outright_series_index_mapping_message::fields_type::price_scale_code");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, contract_multiplier) == 30, "unexpected offset of outright_series_index_mapping_message::fields_type::contract_multiplier");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, maturity_date) == 32, "unexpected offset of outright_series_index_mapping_message::fields_type::maturity_date");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, put_or_call) == 38, "unexpected offset of outright_series_index_mapping_message::fields_type::put_or_call");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, strike_price) == 39, "unexpected offset of outright_series_index_mapping_message::fields_type::strike_price");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, closing_only_indicator) == 49, "unexpected offset of outright_series_index_mapping_message::fields_type::closing_only_indicator");
static_assert(offsetof(outright_series_index_mapping_message::fields_type, reserved_1) == 50, "unexpected offset of outright_series_index_mapping_message::fields_type::reserved_1");
static_assert(sizeof(outright_series_index_mapping_message::fields_type) == 51, "unexpected sizeof outright_series_index_mapping_message::fields_type");
static_assert(sizeof(outright_series_index_mapping_message) == sizeof(pillar_deepfeed::message_header) + 51, "unexpected sizeof outright_series_index_mapping_message");

#pragma pack(pop)
}
