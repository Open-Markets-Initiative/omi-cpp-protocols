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
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementOptionalEx.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/MinPriceIncrementAmount.hpp"
#include "../types/IssueDate.hpp"
#include "../types/DatedDate.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/CouponRate.hpp"
#include "../types/ParValue.hpp"
#include "../types/CouponFrequencyUnit.hpp"
#include "../types/CouponFrequencyPeriod.hpp"
#include "../types/CouponDayCount.hpp"
#include "../types/CountryOfIssue.hpp"
#include "../types/Issuer.hpp"
#include "../types/FinancialInstrumentFullName.hpp"
#include "../types/SecurityAltId.hpp"
#include "../types/SecurityAltIdSource.hpp"
#include "../types/PriceQuoteMethod.hpp"
#include "../types/PartyRoleClearingOrg.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/RiskSet.hpp"
#include "../types/MarketSet.hpp"
#include "../types/InstrumentGuid.hpp"
#include "../types/EventType.hpp"
#include "../types/EventTime.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MdFeedType.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/LotType.hpp"
#include "../types/MinLotSizeDecimalQty.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct md_instrument_definition_fixed_income_events_groups_entry {
    sbe_mdp3::event_type event_type;
    sbe_mdp3::event_time event_time;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_fixed_income_feed_types_groups_entry {
    sbe_mdp3::md_feed_type md_feed_type;
    sbe_mdp3::market_depth market_depth;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_fixed_income_inst_attrib_groups_entry {
    sbe_mdp3::inst_attrib_value inst_attrib_value;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_fixed_income_lot_type_rules_groups_entry {
    sbe_mdp3::lot_type lot_type;
    sbe_mdp3::min_lot_size_decimal_qty min_lot_size_decimal_qty;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Instrument Definition Fixed Income
struct md_instrument_definition_fixed_income {

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
        sbe_mdp3::match_algorithm match_algorithm;
        sbe_mdp3::min_trade_vol min_trade_vol;
        sbe_mdp3::max_trade_vol max_trade_vol;
        sbe_mdp3::min_price_increment_optional_ex min_price_increment_optional_ex;
        sbe_mdp3::display_factor display_factor;
        sbe_mdp3::main_fraction main_fraction;
        sbe_mdp3::sub_fraction sub_fraction;
        sbe_mdp3::price_display_format price_display_format;
        sbe_mdp3::unit_of_measure unit_of_measure;
        sbe_mdp3::unit_of_measure_qty unit_of_measure_qty;
        sbe_mdp3::trading_reference_price trading_reference_price;
        sbe_mdp3::trading_reference_date trading_reference_date;
        sbe_mdp3::high_limit_price high_limit_price;
        sbe_mdp3::low_limit_price low_limit_price;
        sbe_mdp3::max_price_variation max_price_variation;
        sbe_mdp3::min_price_increment_amount min_price_increment_amount;
        sbe_mdp3::issue_date issue_date;
        sbe_mdp3::dated_date dated_date;
        sbe_mdp3::maturity_date maturity_date;
        sbe_mdp3::coupon_rate coupon_rate;
        sbe_mdp3::par_value par_value;
        sbe_mdp3::coupon_frequency_unit coupon_frequency_unit;
        sbe_mdp3::coupon_frequency_period coupon_frequency_period;
        sbe_mdp3::coupon_day_count coupon_day_count;
        sbe_mdp3::country_of_issue country_of_issue;
        sbe_mdp3::issuer issuer;
        sbe_mdp3::financial_instrument_full_name financial_instrument_full_name;
        sbe_mdp3::security_alt_id security_alt_id;
        sbe_mdp3::security_alt_id_source security_alt_id_source;
        sbe_mdp3::price_quote_method price_quote_method;
        sbe_mdp3::party_role_clearing_org party_role_clearing_org;
        sbe_mdp3::user_defined_instrument user_defined_instrument;
        sbe_mdp3::risk_set risk_set;
        sbe_mdp3::market_set market_set;
        sbe_mdp3::instrument_guid instrument_guid;
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
    sbe_group_iterator<md_instrument_definition_fixed_income_events_groups_entry, group_size> events_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_fixed_income_feed_types_groups_entry, group_size> feed_types_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_fixed_income_inst_attrib_groups_entry, group_size> inst_attrib_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_fixed_income_lot_type_rules_groups_entry, group_size> lot_type_rules_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static md_instrument_definition_fixed_income* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_definition_fixed_income*>(buffer);
    }

    // parse method const
    static const md_instrument_definition_fixed_income* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_definition_fixed_income*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, match_event_indicator) == 0, "unexpected offset of md_instrument_definition_fixed_income::fields_type::match_event_indicator");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, tot_num_reports_optional) == 1, "unexpected offset of md_instrument_definition_fixed_income::fields_type::tot_num_reports_optional");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, security_update_action) == 5, "unexpected offset of md_instrument_definition_fixed_income::fields_type::security_update_action");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, last_update_time) == 6, "unexpected offset of md_instrument_definition_fixed_income::fields_type::last_update_time");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, md_security_trading_status) == 14, "unexpected offset of md_instrument_definition_fixed_income::fields_type::md_security_trading_status");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, appl_id) == 15, "unexpected offset of md_instrument_definition_fixed_income::fields_type::appl_id");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, market_segment_id) == 17, "unexpected offset of md_instrument_definition_fixed_income::fields_type::market_segment_id");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, underlying_product) == 18, "unexpected offset of md_instrument_definition_fixed_income::fields_type::underlying_product");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, security_exchange) == 19, "unexpected offset of md_instrument_definition_fixed_income::fields_type::security_exchange");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, security_group) == 23, "unexpected offset of md_instrument_definition_fixed_income::fields_type::security_group");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, asset) == 29, "unexpected offset of md_instrument_definition_fixed_income::fields_type::asset");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, symbol) == 35, "unexpected offset of md_instrument_definition_fixed_income::fields_type::symbol");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, security_id) == 55, "unexpected offset of md_instrument_definition_fixed_income::fields_type::security_id");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, security_type) == 59, "unexpected offset of md_instrument_definition_fixed_income::fields_type::security_type");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, cfi_code) == 65, "unexpected offset of md_instrument_definition_fixed_income::fields_type::cfi_code");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, currency) == 71, "unexpected offset of md_instrument_definition_fixed_income::fields_type::currency");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, settl_currency) == 74, "unexpected offset of md_instrument_definition_fixed_income::fields_type::settl_currency");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, match_algorithm) == 77, "unexpected offset of md_instrument_definition_fixed_income::fields_type::match_algorithm");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, min_trade_vol) == 78, "unexpected offset of md_instrument_definition_fixed_income::fields_type::min_trade_vol");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, max_trade_vol) == 82, "unexpected offset of md_instrument_definition_fixed_income::fields_type::max_trade_vol");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, min_price_increment_optional_ex) == 86, "unexpected offset of md_instrument_definition_fixed_income::fields_type::min_price_increment_optional_ex");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, display_factor) == 94, "unexpected offset of md_instrument_definition_fixed_income::fields_type::display_factor");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, main_fraction) == 102, "unexpected offset of md_instrument_definition_fixed_income::fields_type::main_fraction");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, sub_fraction) == 103, "unexpected offset of md_instrument_definition_fixed_income::fields_type::sub_fraction");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, price_display_format) == 104, "unexpected offset of md_instrument_definition_fixed_income::fields_type::price_display_format");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, unit_of_measure) == 105, "unexpected offset of md_instrument_definition_fixed_income::fields_type::unit_of_measure");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, unit_of_measure_qty) == 135, "unexpected offset of md_instrument_definition_fixed_income::fields_type::unit_of_measure_qty");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, trading_reference_price) == 143, "unexpected offset of md_instrument_definition_fixed_income::fields_type::trading_reference_price");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, trading_reference_date) == 151, "unexpected offset of md_instrument_definition_fixed_income::fields_type::trading_reference_date");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, high_limit_price) == 153, "unexpected offset of md_instrument_definition_fixed_income::fields_type::high_limit_price");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, low_limit_price) == 161, "unexpected offset of md_instrument_definition_fixed_income::fields_type::low_limit_price");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, max_price_variation) == 169, "unexpected offset of md_instrument_definition_fixed_income::fields_type::max_price_variation");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, min_price_increment_amount) == 177, "unexpected offset of md_instrument_definition_fixed_income::fields_type::min_price_increment_amount");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, issue_date) == 185, "unexpected offset of md_instrument_definition_fixed_income::fields_type::issue_date");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, dated_date) == 187, "unexpected offset of md_instrument_definition_fixed_income::fields_type::dated_date");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, maturity_date) == 189, "unexpected offset of md_instrument_definition_fixed_income::fields_type::maturity_date");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, coupon_rate) == 191, "unexpected offset of md_instrument_definition_fixed_income::fields_type::coupon_rate");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, par_value) == 199, "unexpected offset of md_instrument_definition_fixed_income::fields_type::par_value");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, coupon_frequency_unit) == 207, "unexpected offset of md_instrument_definition_fixed_income::fields_type::coupon_frequency_unit");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, coupon_frequency_period) == 210, "unexpected offset of md_instrument_definition_fixed_income::fields_type::coupon_frequency_period");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, coupon_day_count) == 212, "unexpected offset of md_instrument_definition_fixed_income::fields_type::coupon_day_count");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, country_of_issue) == 232, "unexpected offset of md_instrument_definition_fixed_income::fields_type::country_of_issue");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, issuer) == 234, "unexpected offset of md_instrument_definition_fixed_income::fields_type::issuer");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, financial_instrument_full_name) == 259, "unexpected offset of md_instrument_definition_fixed_income::fields_type::financial_instrument_full_name");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, security_alt_id) == 294, "unexpected offset of md_instrument_definition_fixed_income::fields_type::security_alt_id");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, security_alt_id_source) == 306, "unexpected offset of md_instrument_definition_fixed_income::fields_type::security_alt_id_source");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, price_quote_method) == 307, "unexpected offset of md_instrument_definition_fixed_income::fields_type::price_quote_method");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, party_role_clearing_org) == 312, "unexpected offset of md_instrument_definition_fixed_income::fields_type::party_role_clearing_org");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, user_defined_instrument) == 317, "unexpected offset of md_instrument_definition_fixed_income::fields_type::user_defined_instrument");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, risk_set) == 318, "unexpected offset of md_instrument_definition_fixed_income::fields_type::risk_set");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, market_set) == 324, "unexpected offset of md_instrument_definition_fixed_income::fields_type::market_set");
static_assert(offsetof(md_instrument_definition_fixed_income::fields_type, instrument_guid) == 330, "unexpected offset of md_instrument_definition_fixed_income::fields_type::instrument_guid");
static_assert(sizeof(md_instrument_definition_fixed_income::fields_type) == 338, "unexpected sizeof md_instrument_definition_fixed_income::fields_type");

#pragma pack(pop)
}

#include "details/MdInstrumentDefinitionFixedIncomeWriter.hpp"
#include "details/MdInstrumentDefinitionFixedIncomeReader.hpp"
