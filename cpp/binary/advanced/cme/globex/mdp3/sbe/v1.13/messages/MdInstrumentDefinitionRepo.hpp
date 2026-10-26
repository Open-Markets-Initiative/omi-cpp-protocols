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
#include "../types/MinPriceIncrementEx.hpp"
#include "../types/DisplayFactor.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQty.hpp"
#include "../types/TradingReferencePrice.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/HighLimitPrice.hpp"
#include "../types/LowLimitPrice.hpp"
#include "../types/MaxPriceVariation.hpp"
#include "../types/FinancialInstrumentFullName.hpp"
#include "../types/PartyRoleClearingOrg.hpp"
#include "../types/StartDate.hpp"
#include "../types/EndDate.hpp"
#include "../types/TerminationType.hpp"
#include "../types/RepoSubType.hpp"
#include "../types/MoneyOrPar.hpp"
#include "../types/MaxNoOfSubstitutions.hpp"
#include "../types/PriceQuoteMethod.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/RiskSet.hpp"
#include "../types/MarketSet.hpp"
#include "../types/InstrumentGuid.hpp"
#include "../types/TermCode.hpp"
#include "../types/BrokenDateTermType.hpp"
#include "../types/EventType.hpp"
#include "../types/EventTime.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MdFeedType.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/LotType.hpp"
#include "../types/MinLotSizeDecimalQty.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/UnderlyingSecurityIdOptional.hpp"
#include "../types/UnderlyingSecurityAltId.hpp"
#include "../types/UnderlyingSecurityAltIdSource.hpp"
#include "../types/UnderlyingFinancialInstrumentFullName.hpp"
#include "../types/UnderlyingSecurityType.hpp"
#include "../types/UnderlyingCountryOfIssue.hpp"
#include "../types/UnderlyingIssuer.hpp"
#include "../types/UnderlyingMaxLifeTime.hpp"
#include "../types/UnderlyingMinDaysToMaturity.hpp"
#include "../types/UnderlyingInstrumentGuidOptional.hpp"
#include "../types/UnderlyingMaturityDate.hpp"
#include "../types/RelatedSecurityId.hpp"
#include "../types/RelatedSymbol.hpp"
#include "../types/RelatedInstrumentGuid.hpp"
#include "../types/BrokenDateGuid.hpp"
#include "../types/BrokenDateSecurityId.hpp"
#include "../types/BrokenDateStart.hpp"
#include "../types/BrokenDateEnd.hpp"

namespace cme::mdp3::v13 {

namespace sbe_mdp3 = ::cme::mdp3::v13;

#pragma pack(push, 1)
struct md_instrument_definition_repo_events_groups_entry {
    sbe_mdp3::event_type event_type;
    sbe_mdp3::event_time event_time;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_repo_feed_types_groups_entry {
    sbe_mdp3::md_feed_type md_feed_type;
    sbe_mdp3::market_depth market_depth;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_repo_inst_attrib_groups_entry {
    sbe_mdp3::inst_attrib_value inst_attrib_value;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_repo_lot_type_rules_groups_entry {
    sbe_mdp3::lot_type lot_type;
    sbe_mdp3::min_lot_size_decimal_qty min_lot_size_decimal_qty;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_repo_repo_underlyings_groups_entry {
    sbe_mdp3::underlying_symbol underlying_symbol;
    sbe_mdp3::underlying_security_id_optional underlying_security_id_optional;
    sbe_mdp3::underlying_security_alt_id underlying_security_alt_id;
    sbe_mdp3::underlying_security_alt_id_source underlying_security_alt_id_source;
    sbe_mdp3::underlying_financial_instrument_full_name underlying_financial_instrument_full_name;
    sbe_mdp3::underlying_security_type underlying_security_type;
    sbe_mdp3::underlying_country_of_issue underlying_country_of_issue;
    sbe_mdp3::underlying_issuer underlying_issuer;
    sbe_mdp3::underlying_max_life_time underlying_max_life_time;
    sbe_mdp3::underlying_min_days_to_maturity underlying_min_days_to_maturity;
    sbe_mdp3::underlying_instrument_guid_optional underlying_instrument_guid_optional;
    sbe_mdp3::underlying_maturity_date underlying_maturity_date;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_repo_repo_related_instruments_groups_entry {
    sbe_mdp3::related_security_id related_security_id;
    sbe_mdp3::related_symbol related_symbol;
    sbe_mdp3::related_instrument_guid related_instrument_guid;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_repo_broken_dates_groups_entry {
    sbe_mdp3::broken_date_guid broken_date_guid;
    sbe_mdp3::broken_date_security_id broken_date_security_id;
    sbe_mdp3::broken_date_start broken_date_start;
    sbe_mdp3::broken_date_end broken_date_end;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Instrument Definition Repo
struct md_instrument_definition_repo {

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
        sbe_mdp3::min_price_increment_ex min_price_increment_ex;
        sbe_mdp3::display_factor display_factor;
        sbe_mdp3::unit_of_measure unit_of_measure;
        sbe_mdp3::unit_of_measure_qty unit_of_measure_qty;
        sbe_mdp3::trading_reference_price trading_reference_price;
        sbe_mdp3::trading_reference_date trading_reference_date;
        sbe_mdp3::high_limit_price high_limit_price;
        sbe_mdp3::low_limit_price low_limit_price;
        sbe_mdp3::max_price_variation max_price_variation;
        sbe_mdp3::financial_instrument_full_name financial_instrument_full_name;
        sbe_mdp3::party_role_clearing_org party_role_clearing_org;
        sbe_mdp3::start_date start_date;
        sbe_mdp3::end_date end_date;
        sbe_mdp3::termination_type termination_type;
        sbe_mdp3::repo_sub_type repo_sub_type;
        sbe_mdp3::money_or_par money_or_par;
        sbe_mdp3::max_no_of_substitutions max_no_of_substitutions;
        sbe_mdp3::price_quote_method price_quote_method;
        sbe_mdp3::user_defined_instrument user_defined_instrument;
        sbe_mdp3::risk_set risk_set;
        sbe_mdp3::market_set market_set;
        sbe_mdp3::instrument_guid instrument_guid;
        sbe_mdp3::term_code term_code;
        sbe_mdp3::broken_date_term_type broken_date_term_type;
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
    sbe_group_iterator<md_instrument_definition_repo_events_groups_entry, group_size> events_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_repo_feed_types_groups_entry, group_size> feed_types_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_repo_inst_attrib_groups_entry, group_size> inst_attrib_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_repo_lot_type_rules_groups_entry, group_size> lot_type_rules_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_repo_repo_underlyings_groups_entry, group_size> repo_underlyings_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_repo_repo_related_instruments_groups_entry, group_size> repo_related_instruments_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_repo_broken_dates_groups_entry, group_size> broken_dates_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static md_instrument_definition_repo* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_definition_repo*>(buffer);
    }

    // parse method const
    static const md_instrument_definition_repo* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_definition_repo*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_instrument_definition_repo::fields_type, match_event_indicator) == 0, "unexpected offset of md_instrument_definition_repo::fields_type::match_event_indicator");
static_assert(offsetof(md_instrument_definition_repo::fields_type, tot_num_reports_optional) == 1, "unexpected offset of md_instrument_definition_repo::fields_type::tot_num_reports_optional");
static_assert(offsetof(md_instrument_definition_repo::fields_type, security_update_action) == 5, "unexpected offset of md_instrument_definition_repo::fields_type::security_update_action");
static_assert(offsetof(md_instrument_definition_repo::fields_type, last_update_time) == 6, "unexpected offset of md_instrument_definition_repo::fields_type::last_update_time");
static_assert(offsetof(md_instrument_definition_repo::fields_type, md_security_trading_status) == 14, "unexpected offset of md_instrument_definition_repo::fields_type::md_security_trading_status");
static_assert(offsetof(md_instrument_definition_repo::fields_type, appl_id) == 15, "unexpected offset of md_instrument_definition_repo::fields_type::appl_id");
static_assert(offsetof(md_instrument_definition_repo::fields_type, market_segment_id) == 17, "unexpected offset of md_instrument_definition_repo::fields_type::market_segment_id");
static_assert(offsetof(md_instrument_definition_repo::fields_type, underlying_product) == 18, "unexpected offset of md_instrument_definition_repo::fields_type::underlying_product");
static_assert(offsetof(md_instrument_definition_repo::fields_type, security_exchange) == 19, "unexpected offset of md_instrument_definition_repo::fields_type::security_exchange");
static_assert(offsetof(md_instrument_definition_repo::fields_type, security_group) == 23, "unexpected offset of md_instrument_definition_repo::fields_type::security_group");
static_assert(offsetof(md_instrument_definition_repo::fields_type, asset) == 29, "unexpected offset of md_instrument_definition_repo::fields_type::asset");
static_assert(offsetof(md_instrument_definition_repo::fields_type, symbol) == 35, "unexpected offset of md_instrument_definition_repo::fields_type::symbol");
static_assert(offsetof(md_instrument_definition_repo::fields_type, security_id) == 55, "unexpected offset of md_instrument_definition_repo::fields_type::security_id");
static_assert(offsetof(md_instrument_definition_repo::fields_type, security_type) == 59, "unexpected offset of md_instrument_definition_repo::fields_type::security_type");
static_assert(offsetof(md_instrument_definition_repo::fields_type, cfi_code) == 65, "unexpected offset of md_instrument_definition_repo::fields_type::cfi_code");
static_assert(offsetof(md_instrument_definition_repo::fields_type, currency) == 71, "unexpected offset of md_instrument_definition_repo::fields_type::currency");
static_assert(offsetof(md_instrument_definition_repo::fields_type, settl_currency) == 74, "unexpected offset of md_instrument_definition_repo::fields_type::settl_currency");
static_assert(offsetof(md_instrument_definition_repo::fields_type, match_algorithm) == 77, "unexpected offset of md_instrument_definition_repo::fields_type::match_algorithm");
static_assert(offsetof(md_instrument_definition_repo::fields_type, min_trade_vol) == 78, "unexpected offset of md_instrument_definition_repo::fields_type::min_trade_vol");
static_assert(offsetof(md_instrument_definition_repo::fields_type, max_trade_vol) == 82, "unexpected offset of md_instrument_definition_repo::fields_type::max_trade_vol");
static_assert(offsetof(md_instrument_definition_repo::fields_type, min_price_increment_ex) == 86, "unexpected offset of md_instrument_definition_repo::fields_type::min_price_increment_ex");
static_assert(offsetof(md_instrument_definition_repo::fields_type, display_factor) == 94, "unexpected offset of md_instrument_definition_repo::fields_type::display_factor");
static_assert(offsetof(md_instrument_definition_repo::fields_type, unit_of_measure) == 102, "unexpected offset of md_instrument_definition_repo::fields_type::unit_of_measure");
static_assert(offsetof(md_instrument_definition_repo::fields_type, unit_of_measure_qty) == 132, "unexpected offset of md_instrument_definition_repo::fields_type::unit_of_measure_qty");
static_assert(offsetof(md_instrument_definition_repo::fields_type, trading_reference_price) == 140, "unexpected offset of md_instrument_definition_repo::fields_type::trading_reference_price");
static_assert(offsetof(md_instrument_definition_repo::fields_type, trading_reference_date) == 148, "unexpected offset of md_instrument_definition_repo::fields_type::trading_reference_date");
static_assert(offsetof(md_instrument_definition_repo::fields_type, high_limit_price) == 150, "unexpected offset of md_instrument_definition_repo::fields_type::high_limit_price");
static_assert(offsetof(md_instrument_definition_repo::fields_type, low_limit_price) == 158, "unexpected offset of md_instrument_definition_repo::fields_type::low_limit_price");
static_assert(offsetof(md_instrument_definition_repo::fields_type, max_price_variation) == 166, "unexpected offset of md_instrument_definition_repo::fields_type::max_price_variation");
static_assert(offsetof(md_instrument_definition_repo::fields_type, financial_instrument_full_name) == 174, "unexpected offset of md_instrument_definition_repo::fields_type::financial_instrument_full_name");
static_assert(offsetof(md_instrument_definition_repo::fields_type, party_role_clearing_org) == 209, "unexpected offset of md_instrument_definition_repo::fields_type::party_role_clearing_org");
static_assert(offsetof(md_instrument_definition_repo::fields_type, start_date) == 214, "unexpected offset of md_instrument_definition_repo::fields_type::start_date");
static_assert(offsetof(md_instrument_definition_repo::fields_type, end_date) == 216, "unexpected offset of md_instrument_definition_repo::fields_type::end_date");
static_assert(offsetof(md_instrument_definition_repo::fields_type, termination_type) == 218, "unexpected offset of md_instrument_definition_repo::fields_type::termination_type");
static_assert(offsetof(md_instrument_definition_repo::fields_type, repo_sub_type) == 226, "unexpected offset of md_instrument_definition_repo::fields_type::repo_sub_type");
static_assert(offsetof(md_instrument_definition_repo::fields_type, money_or_par) == 227, "unexpected offset of md_instrument_definition_repo::fields_type::money_or_par");
static_assert(offsetof(md_instrument_definition_repo::fields_type, max_no_of_substitutions) == 228, "unexpected offset of md_instrument_definition_repo::fields_type::max_no_of_substitutions");
static_assert(offsetof(md_instrument_definition_repo::fields_type, price_quote_method) == 229, "unexpected offset of md_instrument_definition_repo::fields_type::price_quote_method");
static_assert(offsetof(md_instrument_definition_repo::fields_type, user_defined_instrument) == 234, "unexpected offset of md_instrument_definition_repo::fields_type::user_defined_instrument");
static_assert(offsetof(md_instrument_definition_repo::fields_type, risk_set) == 235, "unexpected offset of md_instrument_definition_repo::fields_type::risk_set");
static_assert(offsetof(md_instrument_definition_repo::fields_type, market_set) == 241, "unexpected offset of md_instrument_definition_repo::fields_type::market_set");
static_assert(offsetof(md_instrument_definition_repo::fields_type, instrument_guid) == 247, "unexpected offset of md_instrument_definition_repo::fields_type::instrument_guid");
static_assert(offsetof(md_instrument_definition_repo::fields_type, term_code) == 255, "unexpected offset of md_instrument_definition_repo::fields_type::term_code");
static_assert(offsetof(md_instrument_definition_repo::fields_type, broken_date_term_type) == 275, "unexpected offset of md_instrument_definition_repo::fields_type::broken_date_term_type");
static_assert(sizeof(md_instrument_definition_repo::fields_type) == 276, "unexpected sizeof md_instrument_definition_repo::fields_type");

#pragma pack(pop)
}

#include "details/MdInstrumentDefinitionRepoWriter.hpp"
#include "details/MdInstrumentDefinitionRepoReader.hpp"
