// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/SimpleInstrumentDefinitionMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../types/Timestamp.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/UnderlyingAssetType.hpp"
#include "../types/UnderlyingAsset.hpp"
#include "../types/ProductGroupCode.hpp"
#include "../types/Exchange.hpp"
#include "../types/InstrumentIdSource.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/MaturityMonthYear.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlementCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinimumSize.hpp"
#include "../types/MaximumSize.hpp"
#include "../types/Tick.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQuantity.hpp"
#include "../types/SettlementPrice.hpp"
#include "../types/SettlementPriceTypeCalcMethod.hpp"
#include "../types/TotalVolume.hpp"
#include "../types/OpenInterestQuantity.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/TradingCollarVariationType.hpp"
#include "../types/TradingCollarVariation.hpp"
#include "../types/Reserved16.hpp"
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)

// Simple Instrument Definition Message
struct simple_instrument_definition_message {

    struct fields_type {
        mach_topofmarket::timestamp timestamp;
        mach_topofmarket::instrument_id instrument_id;
        mach_topofmarket::underlying_asset_type underlying_asset_type;
        mach_topofmarket::underlying_asset underlying_asset;
        mach_topofmarket::product_group_code product_group_code;
        mach_topofmarket::exchange exchange;
        mach_topofmarket::instrument_id_source instrument_id_source;
        mach_topofmarket::instrument_type instrument_type;
        mach_topofmarket::maturity_month_year maturity_month_year;
        mach_topofmarket::currency currency;
        mach_topofmarket::settlement_currency settlement_currency;
        mach_topofmarket::match_algorithm match_algorithm;
        mach_topofmarket::minimum_size minimum_size;
        mach_topofmarket::maximum_size maximum_size;
        mach_topofmarket::tick tick;
        mach_topofmarket::unit_of_measure unit_of_measure;
        mach_topofmarket::unit_of_measure_quantity unit_of_measure_quantity;
        mach_topofmarket::settlement_price settlement_price;
        mach_topofmarket::settlement_price_type_calc_method settlement_price_type_calc_method;
        mach_topofmarket::total_volume total_volume;
        mach_topofmarket::open_interest_quantity open_interest_quantity;
        mach_topofmarket::high_limit_price high_limit_price;
        mach_topofmarket::low_limit_price low_limit_price;
        mach_topofmarket::trading_collar_variation_type trading_collar_variation_type;
        mach_topofmarket::trading_collar_variation trading_collar_variation;
        mach_topofmarket::reserved_16 reserved_16;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::simple_instrument_definition_message;

    fields_type fields;

    // parse method
    static simple_instrument_definition_message* parse(std::byte* buffer) {
        return reinterpret_cast<simple_instrument_definition_message*>(buffer);
    }

    // parse method const
    static const simple_instrument_definition_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const simple_instrument_definition_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(simple_instrument_definition_message::fields_type, timestamp) == 0, "unexpected offset of simple_instrument_definition_message::fields_type::timestamp");
static_assert(offsetof(simple_instrument_definition_message::fields_type, instrument_id) == 8, "unexpected offset of simple_instrument_definition_message::fields_type::instrument_id");
static_assert(offsetof(simple_instrument_definition_message::fields_type, underlying_asset_type) == 12, "unexpected offset of simple_instrument_definition_message::fields_type::underlying_asset_type");
static_assert(offsetof(simple_instrument_definition_message::fields_type, underlying_asset) == 13, "unexpected offset of simple_instrument_definition_message::fields_type::underlying_asset");
static_assert(offsetof(simple_instrument_definition_message::fields_type, product_group_code) == 17, "unexpected offset of simple_instrument_definition_message::fields_type::product_group_code");
static_assert(offsetof(simple_instrument_definition_message::fields_type, exchange) == 23, "unexpected offset of simple_instrument_definition_message::fields_type::exchange");
static_assert(offsetof(simple_instrument_definition_message::fields_type, instrument_id_source) == 27, "unexpected offset of simple_instrument_definition_message::fields_type::instrument_id_source");
static_assert(offsetof(simple_instrument_definition_message::fields_type, instrument_type) == 28, "unexpected offset of simple_instrument_definition_message::fields_type::instrument_type");
static_assert(offsetof(simple_instrument_definition_message::fields_type, maturity_month_year) == 29, "unexpected offset of simple_instrument_definition_message::fields_type::maturity_month_year");
static_assert(offsetof(simple_instrument_definition_message::fields_type, currency) == 33, "unexpected offset of simple_instrument_definition_message::fields_type::currency");
static_assert(offsetof(simple_instrument_definition_message::fields_type, settlement_currency) == 34, "unexpected offset of simple_instrument_definition_message::fields_type::settlement_currency");
static_assert(offsetof(simple_instrument_definition_message::fields_type, match_algorithm) == 35, "unexpected offset of simple_instrument_definition_message::fields_type::match_algorithm");
static_assert(offsetof(simple_instrument_definition_message::fields_type, minimum_size) == 36, "unexpected offset of simple_instrument_definition_message::fields_type::minimum_size");
static_assert(offsetof(simple_instrument_definition_message::fields_type, maximum_size) == 40, "unexpected offset of simple_instrument_definition_message::fields_type::maximum_size");
static_assert(offsetof(simple_instrument_definition_message::fields_type, tick) == 44, "unexpected offset of simple_instrument_definition_message::fields_type::tick");
static_assert(offsetof(simple_instrument_definition_message::fields_type, unit_of_measure) == 52, "unexpected offset of simple_instrument_definition_message::fields_type::unit_of_measure");
static_assert(offsetof(simple_instrument_definition_message::fields_type, unit_of_measure_quantity) == 57, "unexpected offset of simple_instrument_definition_message::fields_type::unit_of_measure_quantity");
static_assert(offsetof(simple_instrument_definition_message::fields_type, settlement_price) == 61, "unexpected offset of simple_instrument_definition_message::fields_type::settlement_price");
static_assert(offsetof(simple_instrument_definition_message::fields_type, settlement_price_type_calc_method) == 69, "unexpected offset of simple_instrument_definition_message::fields_type::settlement_price_type_calc_method");
static_assert(offsetof(simple_instrument_definition_message::fields_type, total_volume) == 70, "unexpected offset of simple_instrument_definition_message::fields_type::total_volume");
static_assert(offsetof(simple_instrument_definition_message::fields_type, open_interest_quantity) == 74, "unexpected offset of simple_instrument_definition_message::fields_type::open_interest_quantity");
static_assert(offsetof(simple_instrument_definition_message::fields_type, high_limit_price) == 78, "unexpected offset of simple_instrument_definition_message::fields_type::high_limit_price");
static_assert(offsetof(simple_instrument_definition_message::fields_type, low_limit_price) == 86, "unexpected offset of simple_instrument_definition_message::fields_type::low_limit_price");
static_assert(offsetof(simple_instrument_definition_message::fields_type, trading_collar_variation_type) == 94, "unexpected offset of simple_instrument_definition_message::fields_type::trading_collar_variation_type");
static_assert(offsetof(simple_instrument_definition_message::fields_type, trading_collar_variation) == 95, "unexpected offset of simple_instrument_definition_message::fields_type::trading_collar_variation");
static_assert(offsetof(simple_instrument_definition_message::fields_type, reserved_16) == 103, "unexpected offset of simple_instrument_definition_message::fields_type::reserved_16");
static_assert(sizeof(simple_instrument_definition_message::fields_type) == 119, "unexpected sizeof simple_instrument_definition_message::fields_type");
static_assert(sizeof(simple_instrument_definition_message) == sizeof(mach_topofmarket::mach_packet_header) + sizeof(mach_topofmarket::message_type) + 119, "unexpected sizeof simple_instrument_definition_message");

#pragma pack(pop)
}
