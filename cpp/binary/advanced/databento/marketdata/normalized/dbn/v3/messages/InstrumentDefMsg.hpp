#pragma once

#include <cstddef>
#include "../structs/RecordHeader.hpp"
#include "../types/TsRecv.hpp"
#include "../types/MinPriceIncrement.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/Expiration.hpp"
#include "../types/Activation.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/MinPriceIncrementAmount.hpp"
#include "../types/PriceRatio.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/RawInstrumentId.hpp"
#include "../types/LegPrice.hpp"
#include "../types/LegDelta.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/UnderlyingId.hpp"
#include "../types/MarketDepthImplied.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinLotSize.hpp"
#include "../types/MinLotSizeBlock.hpp"
#include "../types/MinLotSizeRoundLot.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/DecayQuantity.hpp"
#include "../types/OriginalContractSize.hpp"
#include "../types/LegInstrumentId.hpp"
#include "../types/LegRatioPriceNumerator.hpp"
#include "../types/LegRatioPriceDenominator.hpp"
#include "../types/LegRatioQtyNumerator.hpp"
#include "../types/LegRatioQtyDenominator.hpp"
#include "../types/LegUnderlyingId.hpp"
#include "../types/ApplId.hpp"
#include "../types/MaturityYear.hpp"
#include "../types/DecayStartDate.hpp"
#include "../types/Channel.hpp"
#include "../types/LegCount.hpp"
#include "../types/LegIndex.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/Secsubtype.hpp"
#include "../types/RawSymbol.hpp"
#include "../types/Group.hpp"
#include "../types/Exchange.hpp"
#include "../types/Asset.hpp"
#include "../types/Cfi.hpp"
#include "../types/SecurityType.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/Underlying.hpp"
#include "../types/StrikePriceCurrency.hpp"
#include "../types/LegRawSymbol.hpp"
#include "../types/InstrumentClass.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MainFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/SubFraction.hpp"
#include "../types/UnderlyingProduct.hpp"
#include "../types/SecurityUpdateAction.hpp"
#include "../types/MaturityMonth.hpp"
#include "../types/MaturityDay.hpp"
#include "../types/MaturityWeek.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/ContractMultiplierUnit.hpp"
#include "../types/FlowScheduleType.hpp"
#include "../types/TickRule.hpp"
#include "../types/LegInstrumentClass.hpp"
#include "../types/LegSide.hpp"
#include "../types/Reserved17.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v3;

#pragma pack(push, 1)

// Instrument Def Msg
struct instrument_def_msg {

    struct fields_type {
        dbn_normalized::ts_recv ts_recv;
        dbn_normalized::min_price_increment min_price_increment;
        dbn_normalized::display_factor display_factor;
        dbn_normalized::expiration expiration;
        dbn_normalized::activation activation;
        dbn_normalized::high_limit_price high_limit_price;
        dbn_normalized::low_limit_price low_limit_price;
        dbn_normalized::max_price_variation max_price_variation;
        dbn_normalized::unit_of_measure_qty unit_of_measure_qty;
        dbn_normalized::min_price_increment_amount min_price_increment_amount;
        dbn_normalized::price_ratio price_ratio;
        dbn_normalized::strike_price strike_price;
        dbn_normalized::raw_instrument_id raw_instrument_id;
        dbn_normalized::leg_price leg_price;
        dbn_normalized::leg_delta leg_delta;
        dbn_normalized::inst_attrib_value inst_attrib_value;
        dbn_normalized::underlying_id underlying_id;
        dbn_normalized::market_depth_implied market_depth_implied;
        dbn_normalized::market_depth market_depth;
        dbn_normalized::market_segment_id market_segment_id;
        dbn_normalized::max_trade_vol max_trade_vol;
        dbn_normalized::min_lot_size min_lot_size;
        dbn_normalized::min_lot_size_block min_lot_size_block;
        dbn_normalized::min_lot_size_round_lot min_lot_size_round_lot;
        dbn_normalized::min_trade_vol min_trade_vol;
        dbn_normalized::contract_multiplier contract_multiplier;
        dbn_normalized::decay_quantity decay_quantity;
        dbn_normalized::original_contract_size original_contract_size;
        dbn_normalized::leg_instrument_id leg_instrument_id;
        dbn_normalized::leg_ratio_price_numerator leg_ratio_price_numerator;
        dbn_normalized::leg_ratio_price_denominator leg_ratio_price_denominator;
        dbn_normalized::leg_ratio_qty_numerator leg_ratio_qty_numerator;
        dbn_normalized::leg_ratio_qty_denominator leg_ratio_qty_denominator;
        dbn_normalized::leg_underlying_id leg_underlying_id;
        dbn_normalized::appl_id appl_id;
        dbn_normalized::maturity_year maturity_year;
        dbn_normalized::decay_start_date decay_start_date;
        dbn_normalized::channel channel;
        dbn_normalized::leg_count leg_count;
        dbn_normalized::leg_index leg_index;
        dbn_normalized::currency currency;
        dbn_normalized::settl_currency settl_currency;
        dbn_normalized::secsubtype secsubtype;
        dbn_normalized::raw_symbol raw_symbol;
        dbn_normalized::group group;
        dbn_normalized::exchange exchange;
        dbn_normalized::asset asset;
        dbn_normalized::cfi cfi;
        dbn_normalized::security_type security_type;
        dbn_normalized::unit_of_measure unit_of_measure;
        dbn_normalized::underlying underlying;
        dbn_normalized::strike_price_currency strike_price_currency;
        dbn_normalized::leg_raw_symbol leg_raw_symbol;
        dbn_normalized::instrument_class instrument_class;
        dbn_normalized::match_algorithm match_algorithm;
        dbn_normalized::main_fraction main_fraction;
        dbn_normalized::price_display_format price_display_format;
        dbn_normalized::sub_fraction sub_fraction;
        dbn_normalized::underlying_product underlying_product;
        dbn_normalized::security_update_action security_update_action;
        dbn_normalized::maturity_month maturity_month;
        dbn_normalized::maturity_day maturity_day;
        dbn_normalized::maturity_week maturity_week;
        dbn_normalized::user_defined_instrument user_defined_instrument;
        dbn_normalized::contract_multiplier_unit contract_multiplier_unit;
        dbn_normalized::flow_schedule_type flow_schedule_type;
        dbn_normalized::tick_rule tick_rule;
        dbn_normalized::leg_instrument_class leg_instrument_class;
        dbn_normalized::leg_side leg_side;
        dbn_normalized::reserved_17 reserved_17;
    };

    dbn_normalized::record_header header = {record_length((sizeof(dbn_normalized::record_header) + sizeof(fields_type)) / 4), rtype::enum_type::instrument_definition, {}, {}, {}};

    fields_type fields;

    // parse method
    static instrument_def_msg* parse(std::byte* buffer) {
        return reinterpret_cast<instrument_def_msg*>(buffer);
    }

    // parse method const
    static const instrument_def_msg* parse(const std::byte* buffer) {
        return reinterpret_cast<const instrument_def_msg*>(buffer);
    }

};

// layout verification
static_assert(offsetof(instrument_def_msg::fields_type, ts_recv) == 0, "unexpected offset of instrument_def_msg::fields_type::ts_recv");
static_assert(offsetof(instrument_def_msg::fields_type, min_price_increment) == 8, "unexpected offset of instrument_def_msg::fields_type::min_price_increment");
static_assert(offsetof(instrument_def_msg::fields_type, display_factor) == 16, "unexpected offset of instrument_def_msg::fields_type::display_factor");
static_assert(offsetof(instrument_def_msg::fields_type, expiration) == 24, "unexpected offset of instrument_def_msg::fields_type::expiration");
static_assert(offsetof(instrument_def_msg::fields_type, activation) == 32, "unexpected offset of instrument_def_msg::fields_type::activation");
static_assert(offsetof(instrument_def_msg::fields_type, high_limit_price) == 40, "unexpected offset of instrument_def_msg::fields_type::high_limit_price");
static_assert(offsetof(instrument_def_msg::fields_type, low_limit_price) == 48, "unexpected offset of instrument_def_msg::fields_type::low_limit_price");
static_assert(offsetof(instrument_def_msg::fields_type, max_price_variation) == 56, "unexpected offset of instrument_def_msg::fields_type::max_price_variation");
static_assert(offsetof(instrument_def_msg::fields_type, unit_of_measure_qty) == 64, "unexpected offset of instrument_def_msg::fields_type::unit_of_measure_qty");
static_assert(offsetof(instrument_def_msg::fields_type, min_price_increment_amount) == 72, "unexpected offset of instrument_def_msg::fields_type::min_price_increment_amount");
static_assert(offsetof(instrument_def_msg::fields_type, price_ratio) == 80, "unexpected offset of instrument_def_msg::fields_type::price_ratio");
static_assert(offsetof(instrument_def_msg::fields_type, strike_price) == 88, "unexpected offset of instrument_def_msg::fields_type::strike_price");
static_assert(offsetof(instrument_def_msg::fields_type, raw_instrument_id) == 96, "unexpected offset of instrument_def_msg::fields_type::raw_instrument_id");
static_assert(offsetof(instrument_def_msg::fields_type, leg_price) == 104, "unexpected offset of instrument_def_msg::fields_type::leg_price");
static_assert(offsetof(instrument_def_msg::fields_type, leg_delta) == 112, "unexpected offset of instrument_def_msg::fields_type::leg_delta");
static_assert(offsetof(instrument_def_msg::fields_type, inst_attrib_value) == 120, "unexpected offset of instrument_def_msg::fields_type::inst_attrib_value");
static_assert(offsetof(instrument_def_msg::fields_type, underlying_id) == 124, "unexpected offset of instrument_def_msg::fields_type::underlying_id");
static_assert(offsetof(instrument_def_msg::fields_type, market_depth_implied) == 128, "unexpected offset of instrument_def_msg::fields_type::market_depth_implied");
static_assert(offsetof(instrument_def_msg::fields_type, market_depth) == 132, "unexpected offset of instrument_def_msg::fields_type::market_depth");
static_assert(offsetof(instrument_def_msg::fields_type, market_segment_id) == 136, "unexpected offset of instrument_def_msg::fields_type::market_segment_id");
static_assert(offsetof(instrument_def_msg::fields_type, max_trade_vol) == 140, "unexpected offset of instrument_def_msg::fields_type::max_trade_vol");
static_assert(offsetof(instrument_def_msg::fields_type, min_lot_size) == 144, "unexpected offset of instrument_def_msg::fields_type::min_lot_size");
static_assert(offsetof(instrument_def_msg::fields_type, min_lot_size_block) == 148, "unexpected offset of instrument_def_msg::fields_type::min_lot_size_block");
static_assert(offsetof(instrument_def_msg::fields_type, min_lot_size_round_lot) == 152, "unexpected offset of instrument_def_msg::fields_type::min_lot_size_round_lot");
static_assert(offsetof(instrument_def_msg::fields_type, min_trade_vol) == 156, "unexpected offset of instrument_def_msg::fields_type::min_trade_vol");
static_assert(offsetof(instrument_def_msg::fields_type, contract_multiplier) == 160, "unexpected offset of instrument_def_msg::fields_type::contract_multiplier");
static_assert(offsetof(instrument_def_msg::fields_type, decay_quantity) == 164, "unexpected offset of instrument_def_msg::fields_type::decay_quantity");
static_assert(offsetof(instrument_def_msg::fields_type, original_contract_size) == 168, "unexpected offset of instrument_def_msg::fields_type::original_contract_size");
static_assert(offsetof(instrument_def_msg::fields_type, leg_instrument_id) == 172, "unexpected offset of instrument_def_msg::fields_type::leg_instrument_id");
static_assert(offsetof(instrument_def_msg::fields_type, leg_ratio_price_numerator) == 176, "unexpected offset of instrument_def_msg::fields_type::leg_ratio_price_numerator");
static_assert(offsetof(instrument_def_msg::fields_type, leg_ratio_price_denominator) == 180, "unexpected offset of instrument_def_msg::fields_type::leg_ratio_price_denominator");
static_assert(offsetof(instrument_def_msg::fields_type, leg_ratio_qty_numerator) == 184, "unexpected offset of instrument_def_msg::fields_type::leg_ratio_qty_numerator");
static_assert(offsetof(instrument_def_msg::fields_type, leg_ratio_qty_denominator) == 188, "unexpected offset of instrument_def_msg::fields_type::leg_ratio_qty_denominator");
static_assert(offsetof(instrument_def_msg::fields_type, leg_underlying_id) == 192, "unexpected offset of instrument_def_msg::fields_type::leg_underlying_id");
static_assert(offsetof(instrument_def_msg::fields_type, appl_id) == 196, "unexpected offset of instrument_def_msg::fields_type::appl_id");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_year) == 198, "unexpected offset of instrument_def_msg::fields_type::maturity_year");
static_assert(offsetof(instrument_def_msg::fields_type, decay_start_date) == 200, "unexpected offset of instrument_def_msg::fields_type::decay_start_date");
static_assert(offsetof(instrument_def_msg::fields_type, channel) == 202, "unexpected offset of instrument_def_msg::fields_type::channel");
static_assert(offsetof(instrument_def_msg::fields_type, leg_count) == 204, "unexpected offset of instrument_def_msg::fields_type::leg_count");
static_assert(offsetof(instrument_def_msg::fields_type, leg_index) == 206, "unexpected offset of instrument_def_msg::fields_type::leg_index");
static_assert(offsetof(instrument_def_msg::fields_type, currency) == 208, "unexpected offset of instrument_def_msg::fields_type::currency");
static_assert(offsetof(instrument_def_msg::fields_type, settl_currency) == 212, "unexpected offset of instrument_def_msg::fields_type::settl_currency");
static_assert(offsetof(instrument_def_msg::fields_type, secsubtype) == 216, "unexpected offset of instrument_def_msg::fields_type::secsubtype");
static_assert(offsetof(instrument_def_msg::fields_type, raw_symbol) == 222, "unexpected offset of instrument_def_msg::fields_type::raw_symbol");
static_assert(offsetof(instrument_def_msg::fields_type, group) == 293, "unexpected offset of instrument_def_msg::fields_type::group");
static_assert(offsetof(instrument_def_msg::fields_type, exchange) == 314, "unexpected offset of instrument_def_msg::fields_type::exchange");
static_assert(offsetof(instrument_def_msg::fields_type, asset) == 319, "unexpected offset of instrument_def_msg::fields_type::asset");
static_assert(offsetof(instrument_def_msg::fields_type, cfi) == 330, "unexpected offset of instrument_def_msg::fields_type::cfi");
static_assert(offsetof(instrument_def_msg::fields_type, security_type) == 337, "unexpected offset of instrument_def_msg::fields_type::security_type");
static_assert(offsetof(instrument_def_msg::fields_type, unit_of_measure) == 344, "unexpected offset of instrument_def_msg::fields_type::unit_of_measure");
static_assert(offsetof(instrument_def_msg::fields_type, underlying) == 375, "unexpected offset of instrument_def_msg::fields_type::underlying");
static_assert(offsetof(instrument_def_msg::fields_type, strike_price_currency) == 396, "unexpected offset of instrument_def_msg::fields_type::strike_price_currency");
static_assert(offsetof(instrument_def_msg::fields_type, leg_raw_symbol) == 400, "unexpected offset of instrument_def_msg::fields_type::leg_raw_symbol");
static_assert(offsetof(instrument_def_msg::fields_type, instrument_class) == 471, "unexpected offset of instrument_def_msg::fields_type::instrument_class");
static_assert(offsetof(instrument_def_msg::fields_type, match_algorithm) == 472, "unexpected offset of instrument_def_msg::fields_type::match_algorithm");
static_assert(offsetof(instrument_def_msg::fields_type, main_fraction) == 473, "unexpected offset of instrument_def_msg::fields_type::main_fraction");
static_assert(offsetof(instrument_def_msg::fields_type, price_display_format) == 474, "unexpected offset of instrument_def_msg::fields_type::price_display_format");
static_assert(offsetof(instrument_def_msg::fields_type, sub_fraction) == 475, "unexpected offset of instrument_def_msg::fields_type::sub_fraction");
static_assert(offsetof(instrument_def_msg::fields_type, underlying_product) == 476, "unexpected offset of instrument_def_msg::fields_type::underlying_product");
static_assert(offsetof(instrument_def_msg::fields_type, security_update_action) == 477, "unexpected offset of instrument_def_msg::fields_type::security_update_action");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_month) == 478, "unexpected offset of instrument_def_msg::fields_type::maturity_month");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_day) == 479, "unexpected offset of instrument_def_msg::fields_type::maturity_day");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_week) == 480, "unexpected offset of instrument_def_msg::fields_type::maturity_week");
static_assert(offsetof(instrument_def_msg::fields_type, user_defined_instrument) == 481, "unexpected offset of instrument_def_msg::fields_type::user_defined_instrument");
static_assert(offsetof(instrument_def_msg::fields_type, contract_multiplier_unit) == 482, "unexpected offset of instrument_def_msg::fields_type::contract_multiplier_unit");
static_assert(offsetof(instrument_def_msg::fields_type, flow_schedule_type) == 483, "unexpected offset of instrument_def_msg::fields_type::flow_schedule_type");
static_assert(offsetof(instrument_def_msg::fields_type, tick_rule) == 484, "unexpected offset of instrument_def_msg::fields_type::tick_rule");
static_assert(offsetof(instrument_def_msg::fields_type, leg_instrument_class) == 485, "unexpected offset of instrument_def_msg::fields_type::leg_instrument_class");
static_assert(offsetof(instrument_def_msg::fields_type, leg_side) == 486, "unexpected offset of instrument_def_msg::fields_type::leg_side");
static_assert(offsetof(instrument_def_msg::fields_type, reserved_17) == 487, "unexpected offset of instrument_def_msg::fields_type::reserved_17");
static_assert(sizeof(instrument_def_msg::fields_type) == 504, "unexpected sizeof instrument_def_msg::fields_type");
static_assert(sizeof(instrument_def_msg) == sizeof(dbn_normalized::record_header) + 504, "unexpected sizeof instrument_def_msg");

#pragma pack(pop)
}
