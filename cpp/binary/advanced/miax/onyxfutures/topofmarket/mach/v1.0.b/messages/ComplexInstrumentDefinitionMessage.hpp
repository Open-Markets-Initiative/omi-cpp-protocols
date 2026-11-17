// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/ComplexInstrumentDefinitionMessage.hpp
#pragma once

#include <cstddef>
#include "../structs/MachPacketHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/Timestamp.hpp"
#include "../types/StrategyId.hpp"
#include "../types/UnderlyingAssetType.hpp"
#include "../types/UnderlyingAsset.hpp"
#include "../types/ProductGroupCode.hpp"
#include "../types/SpreadType.hpp"
#include "../types/Exchange.hpp"
#include "../types/InstrumentIdSource.hpp"
#include "../types/InstrumentType.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlementCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinimumSize.hpp"
#include "../types/MaximumSize.hpp"
#include "../types/Tick.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQuantity.hpp"
#include "../types/TradingCollarVariationType.hpp"
#include "../types/TradingCollarVariation.hpp"
#include "../types/Reserved16.hpp"
#include "../types/NumberOfLegs.hpp"
#include "../types/InstrumentId.hpp"
#include "../types/LegRatioAndSide.hpp"
#include "../types/MaturityMonthYear.hpp"
#include "../types/Reserved8.hpp"
#include "../types/MessageType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

namespace mach_topofmarket = ::miax::onyxfutures::topofmarket::mach::v1_0_b;

#pragma pack(push, 1)
struct complex_instrument_definition_message_instrument_leg_entry {
    mach_topofmarket::instrument_id instrument_id;
    mach_topofmarket::leg_ratio_and_side leg_ratio_and_side;
    mach_topofmarket::maturity_month_year maturity_month_year;
    mach_topofmarket::reserved_8 reserved_8;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Complex Instrument Definition Message
struct complex_instrument_definition_message {

    struct fields_type {
        mach_topofmarket::timestamp timestamp;
        mach_topofmarket::strategy_id strategy_id;
        mach_topofmarket::underlying_asset_type underlying_asset_type;
        mach_topofmarket::underlying_asset underlying_asset;
        mach_topofmarket::product_group_code product_group_code;
        mach_topofmarket::spread_type spread_type;
        mach_topofmarket::exchange exchange;
        mach_topofmarket::instrument_id_source instrument_id_source;
        mach_topofmarket::instrument_type instrument_type;
        mach_topofmarket::currency currency;
        mach_topofmarket::settlement_currency settlement_currency;
        mach_topofmarket::match_algorithm match_algorithm;
        mach_topofmarket::minimum_size minimum_size;
        mach_topofmarket::maximum_size maximum_size;
        mach_topofmarket::tick tick;
        mach_topofmarket::unit_of_measure unit_of_measure;
        mach_topofmarket::unit_of_measure_quantity unit_of_measure_quantity;
        mach_topofmarket::trading_collar_variation_type trading_collar_variation_type;
        mach_topofmarket::trading_collar_variation trading_collar_variation;
        mach_topofmarket::reserved_16 reserved_16;
        mach_topofmarket::number_of_legs number_of_legs;
    };

    mach_topofmarket::mach_packet_header header = {{}, std::uint16_t(sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)), packet_type::enum_type::application_message, {}};
    mach_topofmarket::message_type message_type = mach_topofmarket::message_type::enum_type::complex_instrument_definition_message;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(mach_topofmarket::mach_packet_header) - sizeof(fields_type) - sizeof(mach_topofmarket::message_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.packet_length.get().value();
        return sz == sizeof(mach_topofmarket::mach_packet_header) + sizeof(fields_type) + sizeof(mach_topofmarket::message_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(mach_topofmarket::mach_packet_header) - sizeof(fields_type) - sizeof(mach_topofmarket::message_type));
    }

    // sequential access to variable-length regions
    external_count_iterator<complex_instrument_definition_message_instrument_leg_entry> instrument_leg() const {
        return { tail_begin(), fields.number_of_legs.get().value(), tail_end() };
    }


    // parse method
    static complex_instrument_definition_message* parse(std::byte* buffer) {
        return reinterpret_cast<complex_instrument_definition_message*>(buffer);
    }

    // parse method const
    static const complex_instrument_definition_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const complex_instrument_definition_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(complex_instrument_definition_message::fields_type, timestamp) == 0, "unexpected offset of complex_instrument_definition_message::fields_type::timestamp");
static_assert(offsetof(complex_instrument_definition_message::fields_type, strategy_id) == 8, "unexpected offset of complex_instrument_definition_message::fields_type::strategy_id");
static_assert(offsetof(complex_instrument_definition_message::fields_type, underlying_asset_type) == 12, "unexpected offset of complex_instrument_definition_message::fields_type::underlying_asset_type");
static_assert(offsetof(complex_instrument_definition_message::fields_type, underlying_asset) == 13, "unexpected offset of complex_instrument_definition_message::fields_type::underlying_asset");
static_assert(offsetof(complex_instrument_definition_message::fields_type, product_group_code) == 17, "unexpected offset of complex_instrument_definition_message::fields_type::product_group_code");
static_assert(offsetof(complex_instrument_definition_message::fields_type, spread_type) == 23, "unexpected offset of complex_instrument_definition_message::fields_type::spread_type");
static_assert(offsetof(complex_instrument_definition_message::fields_type, exchange) == 24, "unexpected offset of complex_instrument_definition_message::fields_type::exchange");
static_assert(offsetof(complex_instrument_definition_message::fields_type, instrument_id_source) == 28, "unexpected offset of complex_instrument_definition_message::fields_type::instrument_id_source");
static_assert(offsetof(complex_instrument_definition_message::fields_type, instrument_type) == 29, "unexpected offset of complex_instrument_definition_message::fields_type::instrument_type");
static_assert(offsetof(complex_instrument_definition_message::fields_type, currency) == 30, "unexpected offset of complex_instrument_definition_message::fields_type::currency");
static_assert(offsetof(complex_instrument_definition_message::fields_type, settlement_currency) == 31, "unexpected offset of complex_instrument_definition_message::fields_type::settlement_currency");
static_assert(offsetof(complex_instrument_definition_message::fields_type, match_algorithm) == 32, "unexpected offset of complex_instrument_definition_message::fields_type::match_algorithm");
static_assert(offsetof(complex_instrument_definition_message::fields_type, minimum_size) == 33, "unexpected offset of complex_instrument_definition_message::fields_type::minimum_size");
static_assert(offsetof(complex_instrument_definition_message::fields_type, maximum_size) == 37, "unexpected offset of complex_instrument_definition_message::fields_type::maximum_size");
static_assert(offsetof(complex_instrument_definition_message::fields_type, tick) == 41, "unexpected offset of complex_instrument_definition_message::fields_type::tick");
static_assert(offsetof(complex_instrument_definition_message::fields_type, unit_of_measure) == 49, "unexpected offset of complex_instrument_definition_message::fields_type::unit_of_measure");
static_assert(offsetof(complex_instrument_definition_message::fields_type, unit_of_measure_quantity) == 54, "unexpected offset of complex_instrument_definition_message::fields_type::unit_of_measure_quantity");
static_assert(offsetof(complex_instrument_definition_message::fields_type, trading_collar_variation_type) == 58, "unexpected offset of complex_instrument_definition_message::fields_type::trading_collar_variation_type");
static_assert(offsetof(complex_instrument_definition_message::fields_type, trading_collar_variation) == 59, "unexpected offset of complex_instrument_definition_message::fields_type::trading_collar_variation");
static_assert(offsetof(complex_instrument_definition_message::fields_type, reserved_16) == 67, "unexpected offset of complex_instrument_definition_message::fields_type::reserved_16");
static_assert(offsetof(complex_instrument_definition_message::fields_type, number_of_legs) == 83, "unexpected offset of complex_instrument_definition_message::fields_type::number_of_legs");
static_assert(sizeof(complex_instrument_definition_message::fields_type) == 84, "unexpected sizeof complex_instrument_definition_message::fields_type");

#pragma pack(pop)
}

#include "details/ComplexInstrumentDefinitionMessageWriter.hpp"
#include "details/ComplexInstrumentDefinitionMessageReader.hpp"
