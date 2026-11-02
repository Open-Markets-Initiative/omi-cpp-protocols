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
#include "../types/TradingReferencePrice.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/MinPriceIncrementAmount.hpp"
#include "../types/PriceRatio.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/UnderlyingId.hpp"
#include "../types/RawInstrumentId.hpp"
#include "../types/MarketDepthImplied.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinLotSize.hpp"
#include "../types/MinLotSizeBlock.hpp"
#include "../types/MinLotSizeRoundLot.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/Reserved4.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/DecayQuantity.hpp"
#include "../types/OriginalContractSize.hpp"
#include "../types/SecondReserved4.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/ApplId.hpp"
#include "../types/MaturityYear.hpp"
#include "../types/DecayStartDate.hpp"
#include "../types/Channel.hpp"
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
#include "../types/InstrumentClass.hpp"
#include "../types/Reserved2.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/Reserved6.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/MainFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/SettlPriceType.hpp"
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
#include "../types/Dummy3.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

namespace dbn_normalized = ::databento::marketdata::normalized::dbn::v1;

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
        dbn_normalized::trading_reference_price trading_reference_price;
        dbn_normalized::unit_of_measure_qty unit_of_measure_qty;
        dbn_normalized::min_price_increment_amount min_price_increment_amount;
        dbn_normalized::price_ratio price_ratio;
        dbn_normalized::inst_attrib_value inst_attrib_value;
        dbn_normalized::underlying_id underlying_id;
        dbn_normalized::raw_instrument_id raw_instrument_id;
        dbn_normalized::market_depth_implied market_depth_implied;
        dbn_normalized::market_depth market_depth;
        dbn_normalized::market_segment_id market_segment_id;
        dbn_normalized::max_trade_vol max_trade_vol;
        dbn_normalized::min_lot_size min_lot_size;
        dbn_normalized::min_lot_size_block min_lot_size_block;
        dbn_normalized::min_lot_size_round_lot min_lot_size_round_lot;
        dbn_normalized::min_trade_vol min_trade_vol;
        dbn_normalized::reserved_4 reserved_4;
        dbn_normalized::contract_multiplier contract_multiplier;
        dbn_normalized::decay_quantity decay_quantity;
        dbn_normalized::original_contract_size original_contract_size;
        dbn_normalized::second_reserved_4 second_reserved_4;
        dbn_normalized::trading_reference_date trading_reference_date;
        dbn_normalized::appl_id appl_id;
        dbn_normalized::maturity_year maturity_year;
        dbn_normalized::decay_start_date decay_start_date;
        dbn_normalized::channel channel;
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
        dbn_normalized::instrument_class instrument_class;
        dbn_normalized::reserved_2 reserved_2;
        dbn_normalized::strike_price strike_price;
        dbn_normalized::reserved_6 reserved_6;
        dbn_normalized::match_algorithm match_algorithm;
        dbn_normalized::md_security_trading_status md_security_trading_status;
        dbn_normalized::main_fraction main_fraction;
        dbn_normalized::price_display_format price_display_format;
        dbn_normalized::settl_price_type settl_price_type;
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
        dbn_normalized::dummy_3 dummy_3;
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
static_assert(offsetof(instrument_def_msg::fields_type, trading_reference_price) == 64, "unexpected offset of instrument_def_msg::fields_type::trading_reference_price");
static_assert(offsetof(instrument_def_msg::fields_type, unit_of_measure_qty) == 72, "unexpected offset of instrument_def_msg::fields_type::unit_of_measure_qty");
static_assert(offsetof(instrument_def_msg::fields_type, min_price_increment_amount) == 80, "unexpected offset of instrument_def_msg::fields_type::min_price_increment_amount");
static_assert(offsetof(instrument_def_msg::fields_type, price_ratio) == 88, "unexpected offset of instrument_def_msg::fields_type::price_ratio");
static_assert(offsetof(instrument_def_msg::fields_type, inst_attrib_value) == 96, "unexpected offset of instrument_def_msg::fields_type::inst_attrib_value");
static_assert(offsetof(instrument_def_msg::fields_type, underlying_id) == 100, "unexpected offset of instrument_def_msg::fields_type::underlying_id");
static_assert(offsetof(instrument_def_msg::fields_type, raw_instrument_id) == 104, "unexpected offset of instrument_def_msg::fields_type::raw_instrument_id");
static_assert(offsetof(instrument_def_msg::fields_type, market_depth_implied) == 108, "unexpected offset of instrument_def_msg::fields_type::market_depth_implied");
static_assert(offsetof(instrument_def_msg::fields_type, market_depth) == 112, "unexpected offset of instrument_def_msg::fields_type::market_depth");
static_assert(offsetof(instrument_def_msg::fields_type, market_segment_id) == 116, "unexpected offset of instrument_def_msg::fields_type::market_segment_id");
static_assert(offsetof(instrument_def_msg::fields_type, max_trade_vol) == 120, "unexpected offset of instrument_def_msg::fields_type::max_trade_vol");
static_assert(offsetof(instrument_def_msg::fields_type, min_lot_size) == 124, "unexpected offset of instrument_def_msg::fields_type::min_lot_size");
static_assert(offsetof(instrument_def_msg::fields_type, min_lot_size_block) == 128, "unexpected offset of instrument_def_msg::fields_type::min_lot_size_block");
static_assert(offsetof(instrument_def_msg::fields_type, min_lot_size_round_lot) == 132, "unexpected offset of instrument_def_msg::fields_type::min_lot_size_round_lot");
static_assert(offsetof(instrument_def_msg::fields_type, min_trade_vol) == 136, "unexpected offset of instrument_def_msg::fields_type::min_trade_vol");
static_assert(offsetof(instrument_def_msg::fields_type, reserved_4) == 140, "unexpected offset of instrument_def_msg::fields_type::reserved_4");
static_assert(offsetof(instrument_def_msg::fields_type, contract_multiplier) == 144, "unexpected offset of instrument_def_msg::fields_type::contract_multiplier");
static_assert(offsetof(instrument_def_msg::fields_type, decay_quantity) == 148, "unexpected offset of instrument_def_msg::fields_type::decay_quantity");
static_assert(offsetof(instrument_def_msg::fields_type, original_contract_size) == 152, "unexpected offset of instrument_def_msg::fields_type::original_contract_size");
static_assert(offsetof(instrument_def_msg::fields_type, second_reserved_4) == 156, "unexpected offset of instrument_def_msg::fields_type::second_reserved_4");
static_assert(offsetof(instrument_def_msg::fields_type, trading_reference_date) == 160, "unexpected offset of instrument_def_msg::fields_type::trading_reference_date");
static_assert(offsetof(instrument_def_msg::fields_type, appl_id) == 162, "unexpected offset of instrument_def_msg::fields_type::appl_id");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_year) == 164, "unexpected offset of instrument_def_msg::fields_type::maturity_year");
static_assert(offsetof(instrument_def_msg::fields_type, decay_start_date) == 166, "unexpected offset of instrument_def_msg::fields_type::decay_start_date");
static_assert(offsetof(instrument_def_msg::fields_type, channel) == 168, "unexpected offset of instrument_def_msg::fields_type::channel");
static_assert(offsetof(instrument_def_msg::fields_type, currency) == 170, "unexpected offset of instrument_def_msg::fields_type::currency");
static_assert(offsetof(instrument_def_msg::fields_type, settl_currency) == 174, "unexpected offset of instrument_def_msg::fields_type::settl_currency");
static_assert(offsetof(instrument_def_msg::fields_type, secsubtype) == 178, "unexpected offset of instrument_def_msg::fields_type::secsubtype");
static_assert(offsetof(instrument_def_msg::fields_type, raw_symbol) == 184, "unexpected offset of instrument_def_msg::fields_type::raw_symbol");
static_assert(offsetof(instrument_def_msg::fields_type, group) == 206, "unexpected offset of instrument_def_msg::fields_type::group");
static_assert(offsetof(instrument_def_msg::fields_type, exchange) == 227, "unexpected offset of instrument_def_msg::fields_type::exchange");
static_assert(offsetof(instrument_def_msg::fields_type, asset) == 232, "unexpected offset of instrument_def_msg::fields_type::asset");
static_assert(offsetof(instrument_def_msg::fields_type, cfi) == 239, "unexpected offset of instrument_def_msg::fields_type::cfi");
static_assert(offsetof(instrument_def_msg::fields_type, security_type) == 246, "unexpected offset of instrument_def_msg::fields_type::security_type");
static_assert(offsetof(instrument_def_msg::fields_type, unit_of_measure) == 253, "unexpected offset of instrument_def_msg::fields_type::unit_of_measure");
static_assert(offsetof(instrument_def_msg::fields_type, underlying) == 284, "unexpected offset of instrument_def_msg::fields_type::underlying");
static_assert(offsetof(instrument_def_msg::fields_type, strike_price_currency) == 305, "unexpected offset of instrument_def_msg::fields_type::strike_price_currency");
static_assert(offsetof(instrument_def_msg::fields_type, instrument_class) == 309, "unexpected offset of instrument_def_msg::fields_type::instrument_class");
static_assert(offsetof(instrument_def_msg::fields_type, reserved_2) == 310, "unexpected offset of instrument_def_msg::fields_type::reserved_2");
static_assert(offsetof(instrument_def_msg::fields_type, strike_price) == 312, "unexpected offset of instrument_def_msg::fields_type::strike_price");
static_assert(offsetof(instrument_def_msg::fields_type, reserved_6) == 320, "unexpected offset of instrument_def_msg::fields_type::reserved_6");
static_assert(offsetof(instrument_def_msg::fields_type, match_algorithm) == 326, "unexpected offset of instrument_def_msg::fields_type::match_algorithm");
static_assert(offsetof(instrument_def_msg::fields_type, md_security_trading_status) == 327, "unexpected offset of instrument_def_msg::fields_type::md_security_trading_status");
static_assert(offsetof(instrument_def_msg::fields_type, main_fraction) == 328, "unexpected offset of instrument_def_msg::fields_type::main_fraction");
static_assert(offsetof(instrument_def_msg::fields_type, price_display_format) == 329, "unexpected offset of instrument_def_msg::fields_type::price_display_format");
static_assert(offsetof(instrument_def_msg::fields_type, settl_price_type) == 330, "unexpected offset of instrument_def_msg::fields_type::settl_price_type");
static_assert(offsetof(instrument_def_msg::fields_type, sub_fraction) == 331, "unexpected offset of instrument_def_msg::fields_type::sub_fraction");
static_assert(offsetof(instrument_def_msg::fields_type, underlying_product) == 332, "unexpected offset of instrument_def_msg::fields_type::underlying_product");
static_assert(offsetof(instrument_def_msg::fields_type, security_update_action) == 333, "unexpected offset of instrument_def_msg::fields_type::security_update_action");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_month) == 334, "unexpected offset of instrument_def_msg::fields_type::maturity_month");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_day) == 335, "unexpected offset of instrument_def_msg::fields_type::maturity_day");
static_assert(offsetof(instrument_def_msg::fields_type, maturity_week) == 336, "unexpected offset of instrument_def_msg::fields_type::maturity_week");
static_assert(offsetof(instrument_def_msg::fields_type, user_defined_instrument) == 337, "unexpected offset of instrument_def_msg::fields_type::user_defined_instrument");
static_assert(offsetof(instrument_def_msg::fields_type, contract_multiplier_unit) == 338, "unexpected offset of instrument_def_msg::fields_type::contract_multiplier_unit");
static_assert(offsetof(instrument_def_msg::fields_type, flow_schedule_type) == 339, "unexpected offset of instrument_def_msg::fields_type::flow_schedule_type");
static_assert(offsetof(instrument_def_msg::fields_type, tick_rule) == 340, "unexpected offset of instrument_def_msg::fields_type::tick_rule");
static_assert(offsetof(instrument_def_msg::fields_type, dummy_3) == 341, "unexpected offset of instrument_def_msg::fields_type::dummy_3");
static_assert(sizeof(instrument_def_msg::fields_type) == 344, "unexpected sizeof instrument_def_msg::fields_type");
static_assert(sizeof(instrument_def_msg) == sizeof(dbn_normalized::record_header) + 344, "unexpected sizeof instrument_def_msg");

#pragma pack(pop)
}
