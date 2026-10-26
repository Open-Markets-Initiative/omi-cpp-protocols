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
#include "../types/UnderlyingProductOptional.hpp"
#include "../types/SecurityExchange.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Asset.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityType.hpp"
#include "../types/CfiCode.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../types/Currency.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementOptionalEx.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/PriceRatio.hpp"
#include "../types/TickRule.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/OpenInterestQty.hpp"
#include "../types/ClearedVolume.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/PriceQuoteMethod.hpp"
#include "../types/RiskSet.hpp"
#include "../types/MarketSet.hpp"
#include "../types/InstrumentGuid.hpp"
#include "../types/FinancialInstrumentFullName.hpp"
#include "../types/EventType.hpp"
#include "../types/EventTime.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MdFeedType.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/LotType.hpp"
#include "../types/MinLotSizeDecimalQty.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegPrice.hpp"
#include "../types/LegOptionDelta.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct md_instrument_definition_spread_events_groups_entry {
    sbe_mdp3::event_type event_type;
    sbe_mdp3::event_time event_time;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_spread_feed_types_groups_entry {
    sbe_mdp3::md_feed_type md_feed_type;
    sbe_mdp3::market_depth market_depth;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_spread_inst_attrib_groups_entry {
    sbe_mdp3::inst_attrib_value inst_attrib_value;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_spread_lot_type_rules_groups_entry {
    sbe_mdp3::lot_type lot_type;
    sbe_mdp3::min_lot_size_decimal_qty min_lot_size_decimal_qty;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_spread_legs_groups_entry {
    sbe_mdp3::leg_security_id leg_security_id;
    sbe_mdp3::leg_side leg_side;
    sbe_mdp3::leg_ratio_qty leg_ratio_qty;
    sbe_mdp3::leg_price leg_price;
    sbe_mdp3::leg_option_delta leg_option_delta;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Instrument Definition Spread
struct md_instrument_definition_spread {

    struct fields_type {
        sbe_mdp3::match_event_indicator match_event_indicator;
        sbe_mdp3::tot_num_reports_optional tot_num_reports_optional;
        sbe_mdp3::security_update_action security_update_action;
        sbe_mdp3::last_update_time last_update_time;
        sbe_mdp3::md_security_trading_status md_security_trading_status;
        sbe_mdp3::appl_id appl_id;
        sbe_mdp3::market_segment_id market_segment_id;
        sbe_mdp3::underlying_product_optional underlying_product_optional;
        sbe_mdp3::security_exchange security_exchange;
        sbe_mdp3::security_group security_group;
        sbe_mdp3::asset asset;
        sbe_mdp3::symbol symbol;
        sbe_mdp3::security_id security_id;
        sbe_mdp3::security_type security_type;
        sbe_mdp3::cfi_code cfi_code;
        sbe_mdp3::maturity_month_year maturity_month_year;
        sbe_mdp3::currency currency;
        sbe_mdp3::security_sub_type security_sub_type;
        sbe_mdp3::user_defined_instrument user_defined_instrument;
        sbe_mdp3::match_algorithm match_algorithm;
        sbe_mdp3::min_trade_vol min_trade_vol;
        sbe_mdp3::max_trade_vol max_trade_vol;
        sbe_mdp3::min_price_increment_optional_ex min_price_increment_optional_ex;
        sbe_mdp3::display_factor display_factor;
        sbe_mdp3::price_display_format price_display_format;
        sbe_mdp3::price_ratio price_ratio;
        sbe_mdp3::tick_rule tick_rule;
        sbe_mdp3::unit_of_measure unit_of_measure;
        sbe_mdp3::trading_reference_price trading_reference_price;
        sbe_mdp3::settl_price_type settl_price_type;
        sbe_mdp3::open_interest_qty open_interest_qty;
        sbe_mdp3::cleared_volume cleared_volume;
        sbe_mdp3::high_limit_price high_limit_price;
        sbe_mdp3::low_limit_price low_limit_price;
        sbe_mdp3::max_price_variation max_price_variation;
        sbe_mdp3::main_fraction main_fraction;
        sbe_mdp3::sub_fraction sub_fraction;
        sbe_mdp3::trading_reference_date trading_reference_date;
        sbe_mdp3::price_quote_method price_quote_method;
        sbe_mdp3::risk_set risk_set;
        sbe_mdp3::market_set market_set;
        sbe_mdp3::instrument_guid instrument_guid;
        sbe_mdp3::financial_instrument_full_name financial_instrument_full_name;
    };

    sbe_mdp3::message_header header = {std::uint16_t(sizeof(sbe_mdp3::message_header) + sizeof(fields_type)), {}};

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_mdp3::message_header) - sizeof(fields_type);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_size.get().value();
        return sz == sizeof(sbe_mdp3::message_header) + sizeof(fields_type)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_mdp3::message_header) - sizeof(fields_type));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<md_instrument_definition_spread_events_groups_entry, group_size> events_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_spread_feed_types_groups_entry, group_size> feed_types_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_spread_inst_attrib_groups_entry, group_size> inst_attrib_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_spread_lot_type_rules_groups_entry, group_size> lot_type_rules_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_spread_legs_groups_entry, group_size> legs_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static md_instrument_definition_spread* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_definition_spread*>(buffer);
    }

    // parse method const
    static const md_instrument_definition_spread* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_definition_spread*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_instrument_definition_spread::fields_type, match_event_indicator) == 0, "unexpected offset of md_instrument_definition_spread::fields_type::match_event_indicator");
static_assert(offsetof(md_instrument_definition_spread::fields_type, tot_num_reports_optional) == 1, "unexpected offset of md_instrument_definition_spread::fields_type::tot_num_reports_optional");
static_assert(offsetof(md_instrument_definition_spread::fields_type, security_update_action) == 5, "unexpected offset of md_instrument_definition_spread::fields_type::security_update_action");
static_assert(offsetof(md_instrument_definition_spread::fields_type, last_update_time) == 6, "unexpected offset of md_instrument_definition_spread::fields_type::last_update_time");
static_assert(offsetof(md_instrument_definition_spread::fields_type, md_security_trading_status) == 14, "unexpected offset of md_instrument_definition_spread::fields_type::md_security_trading_status");
static_assert(offsetof(md_instrument_definition_spread::fields_type, appl_id) == 15, "unexpected offset of md_instrument_definition_spread::fields_type::appl_id");
static_assert(offsetof(md_instrument_definition_spread::fields_type, market_segment_id) == 17, "unexpected offset of md_instrument_definition_spread::fields_type::market_segment_id");
static_assert(offsetof(md_instrument_definition_spread::fields_type, underlying_product_optional) == 18, "unexpected offset of md_instrument_definition_spread::fields_type::underlying_product_optional");
static_assert(offsetof(md_instrument_definition_spread::fields_type, security_exchange) == 19, "unexpected offset of md_instrument_definition_spread::fields_type::security_exchange");
static_assert(offsetof(md_instrument_definition_spread::fields_type, security_group) == 23, "unexpected offset of md_instrument_definition_spread::fields_type::security_group");
static_assert(offsetof(md_instrument_definition_spread::fields_type, asset) == 29, "unexpected offset of md_instrument_definition_spread::fields_type::asset");
static_assert(offsetof(md_instrument_definition_spread::fields_type, symbol) == 35, "unexpected offset of md_instrument_definition_spread::fields_type::symbol");
static_assert(offsetof(md_instrument_definition_spread::fields_type, security_id) == 55, "unexpected offset of md_instrument_definition_spread::fields_type::security_id");
static_assert(offsetof(md_instrument_definition_spread::fields_type, security_type) == 59, "unexpected offset of md_instrument_definition_spread::fields_type::security_type");
static_assert(offsetof(md_instrument_definition_spread::fields_type, cfi_code) == 65, "unexpected offset of md_instrument_definition_spread::fields_type::cfi_code");
static_assert(offsetof(md_instrument_definition_spread::fields_type, maturity_month_year) == 71, "unexpected offset of md_instrument_definition_spread::fields_type::maturity_month_year");
static_assert(offsetof(md_instrument_definition_spread::fields_type, currency) == 76, "unexpected offset of md_instrument_definition_spread::fields_type::currency");
static_assert(offsetof(md_instrument_definition_spread::fields_type, security_sub_type) == 79, "unexpected offset of md_instrument_definition_spread::fields_type::security_sub_type");
static_assert(offsetof(md_instrument_definition_spread::fields_type, user_defined_instrument) == 84, "unexpected offset of md_instrument_definition_spread::fields_type::user_defined_instrument");
static_assert(offsetof(md_instrument_definition_spread::fields_type, match_algorithm) == 85, "unexpected offset of md_instrument_definition_spread::fields_type::match_algorithm");
static_assert(offsetof(md_instrument_definition_spread::fields_type, min_trade_vol) == 86, "unexpected offset of md_instrument_definition_spread::fields_type::min_trade_vol");
static_assert(offsetof(md_instrument_definition_spread::fields_type, max_trade_vol) == 90, "unexpected offset of md_instrument_definition_spread::fields_type::max_trade_vol");
static_assert(offsetof(md_instrument_definition_spread::fields_type, min_price_increment_optional_ex) == 94, "unexpected offset of md_instrument_definition_spread::fields_type::min_price_increment_optional_ex");
static_assert(offsetof(md_instrument_definition_spread::fields_type, display_factor) == 102, "unexpected offset of md_instrument_definition_spread::fields_type::display_factor");
static_assert(offsetof(md_instrument_definition_spread::fields_type, price_display_format) == 110, "unexpected offset of md_instrument_definition_spread::fields_type::price_display_format");
static_assert(offsetof(md_instrument_definition_spread::fields_type, price_ratio) == 111, "unexpected offset of md_instrument_definition_spread::fields_type::price_ratio");
static_assert(offsetof(md_instrument_definition_spread::fields_type, tick_rule) == 119, "unexpected offset of md_instrument_definition_spread::fields_type::tick_rule");
static_assert(offsetof(md_instrument_definition_spread::fields_type, unit_of_measure) == 120, "unexpected offset of md_instrument_definition_spread::fields_type::unit_of_measure");
static_assert(offsetof(md_instrument_definition_spread::fields_type, trading_reference_price) == 150, "unexpected offset of md_instrument_definition_spread::fields_type::trading_reference_price");
static_assert(offsetof(md_instrument_definition_spread::fields_type, settl_price_type) == 158, "unexpected offset of md_instrument_definition_spread::fields_type::settl_price_type");
static_assert(offsetof(md_instrument_definition_spread::fields_type, open_interest_qty) == 159, "unexpected offset of md_instrument_definition_spread::fields_type::open_interest_qty");
static_assert(offsetof(md_instrument_definition_spread::fields_type, cleared_volume) == 163, "unexpected offset of md_instrument_definition_spread::fields_type::cleared_volume");
static_assert(offsetof(md_instrument_definition_spread::fields_type, high_limit_price) == 167, "unexpected offset of md_instrument_definition_spread::fields_type::high_limit_price");
static_assert(offsetof(md_instrument_definition_spread::fields_type, low_limit_price) == 175, "unexpected offset of md_instrument_definition_spread::fields_type::low_limit_price");
static_assert(offsetof(md_instrument_definition_spread::fields_type, max_price_variation) == 183, "unexpected offset of md_instrument_definition_spread::fields_type::max_price_variation");
static_assert(offsetof(md_instrument_definition_spread::fields_type, main_fraction) == 191, "unexpected offset of md_instrument_definition_spread::fields_type::main_fraction");
static_assert(offsetof(md_instrument_definition_spread::fields_type, sub_fraction) == 192, "unexpected offset of md_instrument_definition_spread::fields_type::sub_fraction");
static_assert(offsetof(md_instrument_definition_spread::fields_type, trading_reference_date) == 193, "unexpected offset of md_instrument_definition_spread::fields_type::trading_reference_date");
static_assert(offsetof(md_instrument_definition_spread::fields_type, price_quote_method) == 195, "unexpected offset of md_instrument_definition_spread::fields_type::price_quote_method");
static_assert(offsetof(md_instrument_definition_spread::fields_type, risk_set) == 200, "unexpected offset of md_instrument_definition_spread::fields_type::risk_set");
static_assert(offsetof(md_instrument_definition_spread::fields_type, market_set) == 206, "unexpected offset of md_instrument_definition_spread::fields_type::market_set");
static_assert(offsetof(md_instrument_definition_spread::fields_type, instrument_guid) == 212, "unexpected offset of md_instrument_definition_spread::fields_type::instrument_guid");
static_assert(offsetof(md_instrument_definition_spread::fields_type, financial_instrument_full_name) == 220, "unexpected offset of md_instrument_definition_spread::fields_type::financial_instrument_full_name");
static_assert(sizeof(md_instrument_definition_spread::fields_type) == 255, "unexpected sizeof md_instrument_definition_spread::fields_type");

#pragma pack(pop)
}

#include "details/MdInstrumentDefinitionSpreadWriter.hpp"
#include "details/MdInstrumentDefinitionSpreadReader.hpp"
