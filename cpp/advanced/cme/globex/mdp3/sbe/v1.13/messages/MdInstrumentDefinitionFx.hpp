#pragma once

#include <cstddef>
#include "../structs/MessageHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/MatchEventIndicator.hpp"
#include "../types/TotNumReportsOptional.hpp"
#include "../types/SecurityUpdateAction.hpp"
#include "../types/LastUpdateTime.hpp"
#include "../types/MdSecurityTradingStatus.hpp"
#include "../types/ApplId.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/UnderlyingProduct.hpp"
#include "../types/SecurityExchange.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Asset.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityType.hpp"
#include "../types/CfiCode.hpp"
#include "../types/Currency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/PriceQuoteCurrency.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementEx.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/PricePrecision.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/FinancialInstrumentFullName.hpp"
#include "../types/FxCurrencySymbol.hpp"
#include "../types/SettlType.hpp"
#include "../types/InterveningDays.hpp"
#include "../types/FxBenchmarkRateFix.hpp"
#include "../types/RateSource.hpp"
#include "../types/FixRateLocalTime.hpp"
#include "../types/FixRateLocalTimeZone.hpp"
#include "../types/MinQuoteLife.hpp"
#include "../types/MaxPriceDiscretionOffset.hpp"
#include "../types/InstrumentGuid.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../types/SettlementLocale.hpp"
#include "../types/AltMinPriceIncrement.hpp"
#include "../types/AltMinQuoteLife.hpp"
#include "../types/AltPriceIncrementConstraint.hpp"
#include "../types/MaxBidAskConstraint.hpp"
#include "../types/EventType.hpp"
#include "../types/EventTime.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MdFeedType.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/LotType.hpp"
#include "../types/MinLotSizeUInt64.hpp"
#include "../types/TradeDate.hpp"
#include "../types/SettlDate.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/SecurityAltId.hpp"
#include "../types/MessageSize.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct md_instrument_definition_fx_events_groups_entry {
    sbe_mdp3::event_type event_type;
    sbe_mdp3::event_time event_time;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_fx_feed_types_groups_entry {
    sbe_mdp3::md_feed_type md_feed_type;
    sbe_mdp3::market_depth market_depth;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_fx_inst_attrib_groups_entry {
    sbe_mdp3::inst_attrib_value inst_attrib_value;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_fx_fx_lot_type_rules_groups_entry {
    sbe_mdp3::lot_type lot_type;
    sbe_mdp3::min_lot_size_u_int_64 min_lot_size_u_int_64;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_fx_trading_sessions_groups_entry {
    sbe_mdp3::trade_date trade_date;
    sbe_mdp3::settl_date settl_date;
    sbe_mdp3::maturity_date maturity_date;
    sbe_mdp3::security_alt_id security_alt_id;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Instrument Definition Fx
struct md_instrument_definition_fx {

    struct fields_type {
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::tot_num_reports_optional tot_num_reports_optional;
        sbe_mdp3::security_update_action security_update_action;
        sbe_mdp3::last_update_time last_update_time;
        sbe_mdp3::md_security_trading_status md_security_trading_status;
        sbe_mdp3::appl_id appl_id;
        sbe_mdp3::market_segment_id market_segment_id;
        sbe_mdp3::underlying_product underlying_product;
        sbe_mdp3::security_exchange security_exchange;
        sbe_mdp3::security_group security_group;
        sbe_mdp3::asset asset;
        sbe_mdp3::symbol symbol;
        sbe_mdp3::security_id security_id;
        sbe_mdp3::security_type security_type;
        sbe_mdp3::cfi_code cfi_code;
        sbe_mdp3::currency currency;
        sbe_mdp3::settl_currency settl_currency;
        sbe_mdp3::price_quote_currency price_quote_currency;
        sbe_mdp3::match_algorithm match_algorithm;
        sbe_mdp3::min_trade_vol min_trade_vol;
        sbe_mdp3::max_trade_vol max_trade_vol;
        sbe_mdp3::min_price_increment_ex min_price_increment_ex;
        sbe_mdp3::display_factor display_factor;
        sbe_mdp3::price_precision price_precision;
        sbe_mdp3::unit_of_measure unit_of_measure;
        sbe_mdp3::unit_of_measure_qty unit_of_measure_qty;
        sbe_mdp3::high_limit_price high_limit_price;
        sbe_mdp3::low_limit_price low_limit_price;
        sbe_mdp3::max_price_variation max_price_variation;
        sbe_mdp3::user_defined_instrument user_defined_instrument;
        sbe_mdp3::financial_instrument_full_name financial_instrument_full_name;
        sbe_mdp3::fx_currency_symbol fx_currency_symbol;
        sbe_mdp3::settl_type settl_type;
        sbe_mdp3::intervening_days intervening_days;
        sbe_mdp3::fx_benchmark_rate_fix fx_benchmark_rate_fix;
        sbe_mdp3::rate_source rate_source;
        sbe_mdp3::fix_rate_local_time fix_rate_local_time;
        sbe_mdp3::fix_rate_local_time_zone fix_rate_local_time_zone;
        sbe_mdp3::min_quote_life min_quote_life;
        sbe_mdp3::max_price_discretion_offset max_price_discretion_offset;
        sbe_mdp3::instrument_guid instrument_guid;
        sbe_mdp3::maturity_month_year maturity_month_year;
        sbe_mdp3::settlement_locale settlement_locale;
        sbe_mdp3::alt_min_price_increment alt_min_price_increment;
        sbe_mdp3::alt_min_quote_life alt_min_quote_life;
        sbe_mdp3::alt_price_increment_constraint alt_price_increment_constraint;
        sbe_mdp3::max_bid_ask_constraint max_bid_ask_constraint;
    };

    // Transport framing: message size precedes the SBE header on the wire
    sbe_mdp3::message_size message_size;
    sbe_mdp3::message_header header = {{}, template_id::enum_type::md_instrument_definition_fx, schema_id::enum_type::mktdata, version(13)};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type) + sizeof(sbe_mdp3::message_size)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type) - sizeof(sbe_mdp3::message_size));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<md_instrument_definition_fx_events_groups_entry, group_size> events_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_fx_feed_types_groups_entry, group_size> feed_types_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_fx_inst_attrib_groups_entry, group_size> inst_attrib_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_fx_fx_lot_type_rules_groups_entry, group_size> fx_lot_type_rules_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_fx_trading_sessions_groups_entry, group_size> trading_sessions_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static md_instrument_definition_fx* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_definition_fx*>(buffer);
    }

    // parse method const
    static const md_instrument_definition_fx* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_definition_fx*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_instrument_definition_fx::fields_type, match_event_indicator) == 0, "unexpected offset of md_instrument_definition_fx::fields_type::match_event_indicator");
static_assert(offsetof(md_instrument_definition_fx::fields_type, tot_num_reports_optional) == 1, "unexpected offset of md_instrument_definition_fx::fields_type::tot_num_reports_optional");
static_assert(offsetof(md_instrument_definition_fx::fields_type, security_update_action) == 5, "unexpected offset of md_instrument_definition_fx::fields_type::security_update_action");
static_assert(offsetof(md_instrument_definition_fx::fields_type, last_update_time) == 6, "unexpected offset of md_instrument_definition_fx::fields_type::last_update_time");
static_assert(offsetof(md_instrument_definition_fx::fields_type, md_security_trading_status) == 14, "unexpected offset of md_instrument_definition_fx::fields_type::md_security_trading_status");
static_assert(offsetof(md_instrument_definition_fx::fields_type, appl_id) == 15, "unexpected offset of md_instrument_definition_fx::fields_type::appl_id");
static_assert(offsetof(md_instrument_definition_fx::fields_type, market_segment_id) == 17, "unexpected offset of md_instrument_definition_fx::fields_type::market_segment_id");
static_assert(offsetof(md_instrument_definition_fx::fields_type, underlying_product) == 18, "unexpected offset of md_instrument_definition_fx::fields_type::underlying_product");
static_assert(offsetof(md_instrument_definition_fx::fields_type, security_exchange) == 19, "unexpected offset of md_instrument_definition_fx::fields_type::security_exchange");
static_assert(offsetof(md_instrument_definition_fx::fields_type, security_group) == 23, "unexpected offset of md_instrument_definition_fx::fields_type::security_group");
static_assert(offsetof(md_instrument_definition_fx::fields_type, asset) == 29, "unexpected offset of md_instrument_definition_fx::fields_type::asset");
static_assert(offsetof(md_instrument_definition_fx::fields_type, symbol) == 35, "unexpected offset of md_instrument_definition_fx::fields_type::symbol");
static_assert(offsetof(md_instrument_definition_fx::fields_type, security_id) == 55, "unexpected offset of md_instrument_definition_fx::fields_type::security_id");
static_assert(offsetof(md_instrument_definition_fx::fields_type, security_type) == 59, "unexpected offset of md_instrument_definition_fx::fields_type::security_type");
static_assert(offsetof(md_instrument_definition_fx::fields_type, cfi_code) == 65, "unexpected offset of md_instrument_definition_fx::fields_type::cfi_code");
static_assert(offsetof(md_instrument_definition_fx::fields_type, currency) == 71, "unexpected offset of md_instrument_definition_fx::fields_type::currency");
static_assert(offsetof(md_instrument_definition_fx::fields_type, settl_currency) == 74, "unexpected offset of md_instrument_definition_fx::fields_type::settl_currency");
static_assert(offsetof(md_instrument_definition_fx::fields_type, price_quote_currency) == 77, "unexpected offset of md_instrument_definition_fx::fields_type::price_quote_currency");
static_assert(offsetof(md_instrument_definition_fx::fields_type, match_algorithm) == 80, "unexpected offset of md_instrument_definition_fx::fields_type::match_algorithm");
static_assert(offsetof(md_instrument_definition_fx::fields_type, min_trade_vol) == 81, "unexpected offset of md_instrument_definition_fx::fields_type::min_trade_vol");
static_assert(offsetof(md_instrument_definition_fx::fields_type, max_trade_vol) == 85, "unexpected offset of md_instrument_definition_fx::fields_type::max_trade_vol");
static_assert(offsetof(md_instrument_definition_fx::fields_type, min_price_increment_ex) == 89, "unexpected offset of md_instrument_definition_fx::fields_type::min_price_increment_ex");
static_assert(offsetof(md_instrument_definition_fx::fields_type, display_factor) == 97, "unexpected offset of md_instrument_definition_fx::fields_type::display_factor");
static_assert(offsetof(md_instrument_definition_fx::fields_type, price_precision) == 105, "unexpected offset of md_instrument_definition_fx::fields_type::price_precision");
static_assert(offsetof(md_instrument_definition_fx::fields_type, unit_of_measure) == 106, "unexpected offset of md_instrument_definition_fx::fields_type::unit_of_measure");
static_assert(offsetof(md_instrument_definition_fx::fields_type, unit_of_measure_qty) == 136, "unexpected offset of md_instrument_definition_fx::fields_type::unit_of_measure_qty");
static_assert(offsetof(md_instrument_definition_fx::fields_type, high_limit_price) == 144, "unexpected offset of md_instrument_definition_fx::fields_type::high_limit_price");
static_assert(offsetof(md_instrument_definition_fx::fields_type, low_limit_price) == 152, "unexpected offset of md_instrument_definition_fx::fields_type::low_limit_price");
static_assert(offsetof(md_instrument_definition_fx::fields_type, max_price_variation) == 160, "unexpected offset of md_instrument_definition_fx::fields_type::max_price_variation");
static_assert(offsetof(md_instrument_definition_fx::fields_type, user_defined_instrument) == 168, "unexpected offset of md_instrument_definition_fx::fields_type::user_defined_instrument");
static_assert(offsetof(md_instrument_definition_fx::fields_type, financial_instrument_full_name) == 169, "unexpected offset of md_instrument_definition_fx::fields_type::financial_instrument_full_name");
static_assert(offsetof(md_instrument_definition_fx::fields_type, fx_currency_symbol) == 204, "unexpected offset of md_instrument_definition_fx::fields_type::fx_currency_symbol");
static_assert(offsetof(md_instrument_definition_fx::fields_type, settl_type) == 211, "unexpected offset of md_instrument_definition_fx::fields_type::settl_type");
static_assert(offsetof(md_instrument_definition_fx::fields_type, intervening_days) == 214, "unexpected offset of md_instrument_definition_fx::fields_type::intervening_days");
static_assert(offsetof(md_instrument_definition_fx::fields_type, fx_benchmark_rate_fix) == 216, "unexpected offset of md_instrument_definition_fx::fields_type::fx_benchmark_rate_fix");
static_assert(offsetof(md_instrument_definition_fx::fields_type, rate_source) == 236, "unexpected offset of md_instrument_definition_fx::fields_type::rate_source");
static_assert(offsetof(md_instrument_definition_fx::fields_type, fix_rate_local_time) == 248, "unexpected offset of md_instrument_definition_fx::fields_type::fix_rate_local_time");
static_assert(offsetof(md_instrument_definition_fx::fields_type, fix_rate_local_time_zone) == 256, "unexpected offset of md_instrument_definition_fx::fields_type::fix_rate_local_time_zone");
static_assert(offsetof(md_instrument_definition_fx::fields_type, min_quote_life) == 276, "unexpected offset of md_instrument_definition_fx::fields_type::min_quote_life");
static_assert(offsetof(md_instrument_definition_fx::fields_type, max_price_discretion_offset) == 280, "unexpected offset of md_instrument_definition_fx::fields_type::max_price_discretion_offset");
static_assert(offsetof(md_instrument_definition_fx::fields_type, instrument_guid) == 288, "unexpected offset of md_instrument_definition_fx::fields_type::instrument_guid");
static_assert(offsetof(md_instrument_definition_fx::fields_type, maturity_month_year) == 296, "unexpected offset of md_instrument_definition_fx::fields_type::maturity_month_year");
static_assert(offsetof(md_instrument_definition_fx::fields_type, settlement_locale) == 301, "unexpected offset of md_instrument_definition_fx::fields_type::settlement_locale");
static_assert(offsetof(md_instrument_definition_fx::fields_type, alt_min_price_increment) == 309, "unexpected offset of md_instrument_definition_fx::fields_type::alt_min_price_increment");
static_assert(offsetof(md_instrument_definition_fx::fields_type, alt_min_quote_life) == 317, "unexpected offset of md_instrument_definition_fx::fields_type::alt_min_quote_life");
static_assert(offsetof(md_instrument_definition_fx::fields_type, alt_price_increment_constraint) == 321, "unexpected offset of md_instrument_definition_fx::fields_type::alt_price_increment_constraint");
static_assert(offsetof(md_instrument_definition_fx::fields_type, max_bid_ask_constraint) == 329, "unexpected offset of md_instrument_definition_fx::fields_type::max_bid_ask_constraint");
static_assert(sizeof(md_instrument_definition_fx::fields_type) == 337, "unexpected sizeof md_instrument_definition_fx::fields_type");

#pragma pack(pop)
}

#include "details/MdInstrumentDefinitionFxWriter.hpp"
#include "details/MdInstrumentDefinitionFxReader.hpp"
