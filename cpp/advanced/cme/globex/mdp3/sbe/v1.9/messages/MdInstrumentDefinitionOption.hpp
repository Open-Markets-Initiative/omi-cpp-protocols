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
#include "../types/PutOrCall.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../types/Currency.hpp"
#include "../types/StrikePriceEx.hpp"
#include "../types/StrikeCurrency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/MinCabPriceEx.hpp"
#include "../types/MatchAlgorithm.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/MaxTradeVol.hpp"
#include "../types/MinPriceIncrementOptionalEx.hpp"
#include "../types/MinPriceIncrementAmountEx.hpp"
#include "../types/DisplayFactorEx.hpp"
#include "../types/TickRule.hpp"
#include "../types/MainFraction.hpp"
#include "../types/SubFraction.hpp"
#include "../types/PriceDisplayFormat.hpp"
#include "../types/UnitOfMeasure.hpp"
#include "../types/UnitOfMeasureQtyEx.hpp"
#include "../types/TradingReferencePriceEx.hpp"
#include "../types/SettlPriceType.hpp"
#include "../types/ClearedVolume.hpp"
#include "../types/OpenInterestQty.hpp"
#include "../types/LowLimitPriceEx.hpp"
#include "../types/HighLimitPriceEx.hpp"
#include "../types/UserDefinedInstrument.hpp"
#include "../types/TradingReferenceDate.hpp"
#include "../types/EventType.hpp"
#include "../types/EventTime.hpp"
#include "../structs/GroupSize.hpp"
#include "../types/MdFeedType.hpp"
#include "../types/MarketDepth.hpp"
#include "../types/InstAttribValue.hpp"
#include "../types/LotType.hpp"
#include "../types/MinLotSize.hpp"
#include "../types/UnderlyingSecurityId.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../types/RelatedSecurityId.hpp"
#include "../types/RelatedSymbol.hpp"

namespace cme::mdp3::v9 {

namespace sbe_mdp3 = ::cme::mdp3::v9;

#pragma pack(push, 1)
struct md_instrument_definition_option_events_groups_entry {
    sbe_mdp3::event_type event_type;
    sbe_mdp3::event_time event_time;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_option_feed_types_groups_entry {
    sbe_mdp3::md_feed_type md_feed_type;
    sbe_mdp3::market_depth market_depth;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_option_inst_attrib_groups_entry {
    sbe_mdp3::inst_attrib_value inst_attrib_value;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_option_lot_type_rules_groups_entry {
    sbe_mdp3::lot_type lot_type;
    sbe_mdp3::min_lot_size min_lot_size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_option_option_underlyings_groups_entry {
    sbe_mdp3::underlying_security_id underlying_security_id;
    sbe_mdp3::underlying_symbol underlying_symbol;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct md_instrument_definition_option_option_related_instruments_groups_entry {
    sbe_mdp3::related_security_id related_security_id;
    sbe_mdp3::related_symbol related_symbol;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Md Instrument Definition Option
struct md_instrument_definition_option {

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
        sbe_mdp3::put_or_call put_or_call;
        sbe_mdp3::maturity_month_year maturity_month_year;
        sbe_mdp3::currency currency;
        sbe_mdp3::strike_price_ex strike_price_ex;
        sbe_mdp3::strike_currency strike_currency;
        sbe_mdp3::settl_currency settl_currency;
        sbe_mdp3::min_cab_price_ex min_cab_price_ex;
        sbe_mdp3::match_algorithm match_algorithm;
        sbe_mdp3::min_trade_vol min_trade_vol;
        sbe_mdp3::max_trade_vol max_trade_vol;
        sbe_mdp3::min_price_increment_optional_ex min_price_increment_optional_ex;
        sbe_mdp3::min_price_increment_amount_ex min_price_increment_amount_ex;
        sbe_mdp3::display_factor_ex display_factor_ex;
        sbe_mdp3::tick_rule tick_rule;
        sbe_mdp3::main_fraction main_fraction;
        sbe_mdp3::sub_fraction sub_fraction;
        sbe_mdp3::price_display_format price_display_format;
        sbe_mdp3::unit_of_measure unit_of_measure;
        sbe_mdp3::unit_of_measure_qty_ex unit_of_measure_qty_ex;
        sbe_mdp3::trading_reference_price_ex trading_reference_price_ex;
        sbe_mdp3::settl_price_type settl_price_type;
        sbe_mdp3::cleared_volume cleared_volume;
        sbe_mdp3::open_interest_qty open_interest_qty;
        sbe_mdp3::low_limit_price_ex low_limit_price_ex;
        sbe_mdp3::high_limit_price_ex high_limit_price_ex;
        sbe_mdp3::user_defined_instrument user_defined_instrument;
        sbe_mdp3::trading_reference_date trading_reference_date;
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
    sbe_group_iterator<md_instrument_definition_option_events_groups_entry, group_size> events_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_option_feed_types_groups_entry, group_size> feed_types_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_option_inst_attrib_groups_entry, group_size> inst_attrib_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_option_lot_type_rules_groups_entry, group_size> lot_type_rules_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_option_option_underlyings_groups_entry, group_size> option_underlyings_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<md_instrument_definition_option_option_related_instruments_groups_entry, group_size> option_related_instruments_groups(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static md_instrument_definition_option* parse(std::byte* buffer) {
        return reinterpret_cast<md_instrument_definition_option*>(buffer);
    }

    // parse method const
    static const md_instrument_definition_option* parse(const std::byte* buffer) {
        return reinterpret_cast<const md_instrument_definition_option*>(buffer);
    }

};

// layout verification
static_assert(offsetof(md_instrument_definition_option::fields_type, match_event_indicator) == 0, "unexpected offset of md_instrument_definition_option::fields_type::match_event_indicator");
static_assert(offsetof(md_instrument_definition_option::fields_type, tot_num_reports_optional) == 1, "unexpected offset of md_instrument_definition_option::fields_type::tot_num_reports_optional");
static_assert(offsetof(md_instrument_definition_option::fields_type, security_update_action) == 5, "unexpected offset of md_instrument_definition_option::fields_type::security_update_action");
static_assert(offsetof(md_instrument_definition_option::fields_type, last_update_time) == 6, "unexpected offset of md_instrument_definition_option::fields_type::last_update_time");
static_assert(offsetof(md_instrument_definition_option::fields_type, md_security_trading_status) == 14, "unexpected offset of md_instrument_definition_option::fields_type::md_security_trading_status");
static_assert(offsetof(md_instrument_definition_option::fields_type, appl_id) == 15, "unexpected offset of md_instrument_definition_option::fields_type::appl_id");
static_assert(offsetof(md_instrument_definition_option::fields_type, market_segment_id) == 17, "unexpected offset of md_instrument_definition_option::fields_type::market_segment_id");
static_assert(offsetof(md_instrument_definition_option::fields_type, underlying_product) == 18, "unexpected offset of md_instrument_definition_option::fields_type::underlying_product");
static_assert(offsetof(md_instrument_definition_option::fields_type, security_exchange) == 19, "unexpected offset of md_instrument_definition_option::fields_type::security_exchange");
static_assert(offsetof(md_instrument_definition_option::fields_type, security_group) == 23, "unexpected offset of md_instrument_definition_option::fields_type::security_group");
static_assert(offsetof(md_instrument_definition_option::fields_type, asset) == 29, "unexpected offset of md_instrument_definition_option::fields_type::asset");
static_assert(offsetof(md_instrument_definition_option::fields_type, symbol) == 35, "unexpected offset of md_instrument_definition_option::fields_type::symbol");
static_assert(offsetof(md_instrument_definition_option::fields_type, security_id) == 55, "unexpected offset of md_instrument_definition_option::fields_type::security_id");
static_assert(offsetof(md_instrument_definition_option::fields_type, security_type) == 59, "unexpected offset of md_instrument_definition_option::fields_type::security_type");
static_assert(offsetof(md_instrument_definition_option::fields_type, cfi_code) == 65, "unexpected offset of md_instrument_definition_option::fields_type::cfi_code");
static_assert(offsetof(md_instrument_definition_option::fields_type, put_or_call) == 71, "unexpected offset of md_instrument_definition_option::fields_type::put_or_call");
static_assert(offsetof(md_instrument_definition_option::fields_type, maturity_month_year) == 72, "unexpected offset of md_instrument_definition_option::fields_type::maturity_month_year");
static_assert(offsetof(md_instrument_definition_option::fields_type, currency) == 77, "unexpected offset of md_instrument_definition_option::fields_type::currency");
static_assert(offsetof(md_instrument_definition_option::fields_type, strike_price_ex) == 80, "unexpected offset of md_instrument_definition_option::fields_type::strike_price_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, strike_currency) == 88, "unexpected offset of md_instrument_definition_option::fields_type::strike_currency");
static_assert(offsetof(md_instrument_definition_option::fields_type, settl_currency) == 91, "unexpected offset of md_instrument_definition_option::fields_type::settl_currency");
static_assert(offsetof(md_instrument_definition_option::fields_type, min_cab_price_ex) == 94, "unexpected offset of md_instrument_definition_option::fields_type::min_cab_price_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, match_algorithm) == 102, "unexpected offset of md_instrument_definition_option::fields_type::match_algorithm");
static_assert(offsetof(md_instrument_definition_option::fields_type, min_trade_vol) == 103, "unexpected offset of md_instrument_definition_option::fields_type::min_trade_vol");
static_assert(offsetof(md_instrument_definition_option::fields_type, max_trade_vol) == 107, "unexpected offset of md_instrument_definition_option::fields_type::max_trade_vol");
static_assert(offsetof(md_instrument_definition_option::fields_type, min_price_increment_optional_ex) == 111, "unexpected offset of md_instrument_definition_option::fields_type::min_price_increment_optional_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, min_price_increment_amount_ex) == 119, "unexpected offset of md_instrument_definition_option::fields_type::min_price_increment_amount_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, display_factor_ex) == 127, "unexpected offset of md_instrument_definition_option::fields_type::display_factor_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, tick_rule) == 135, "unexpected offset of md_instrument_definition_option::fields_type::tick_rule");
static_assert(offsetof(md_instrument_definition_option::fields_type, main_fraction) == 136, "unexpected offset of md_instrument_definition_option::fields_type::main_fraction");
static_assert(offsetof(md_instrument_definition_option::fields_type, sub_fraction) == 137, "unexpected offset of md_instrument_definition_option::fields_type::sub_fraction");
static_assert(offsetof(md_instrument_definition_option::fields_type, price_display_format) == 138, "unexpected offset of md_instrument_definition_option::fields_type::price_display_format");
static_assert(offsetof(md_instrument_definition_option::fields_type, unit_of_measure) == 139, "unexpected offset of md_instrument_definition_option::fields_type::unit_of_measure");
static_assert(offsetof(md_instrument_definition_option::fields_type, unit_of_measure_qty_ex) == 169, "unexpected offset of md_instrument_definition_option::fields_type::unit_of_measure_qty_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, trading_reference_price_ex) == 177, "unexpected offset of md_instrument_definition_option::fields_type::trading_reference_price_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, settl_price_type) == 185, "unexpected offset of md_instrument_definition_option::fields_type::settl_price_type");
static_assert(offsetof(md_instrument_definition_option::fields_type, cleared_volume) == 186, "unexpected offset of md_instrument_definition_option::fields_type::cleared_volume");
static_assert(offsetof(md_instrument_definition_option::fields_type, open_interest_qty) == 190, "unexpected offset of md_instrument_definition_option::fields_type::open_interest_qty");
static_assert(offsetof(md_instrument_definition_option::fields_type, low_limit_price_ex) == 194, "unexpected offset of md_instrument_definition_option::fields_type::low_limit_price_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, high_limit_price_ex) == 202, "unexpected offset of md_instrument_definition_option::fields_type::high_limit_price_ex");
static_assert(offsetof(md_instrument_definition_option::fields_type, user_defined_instrument) == 210, "unexpected offset of md_instrument_definition_option::fields_type::user_defined_instrument");
static_assert(offsetof(md_instrument_definition_option::fields_type, trading_reference_date) == 211, "unexpected offset of md_instrument_definition_option::fields_type::trading_reference_date");
static_assert(sizeof(md_instrument_definition_option::fields_type) == 213, "unexpected sizeof md_instrument_definition_option::fields_type");

#pragma pack(pop)
}

#include "details/MdInstrumentDefinitionOptionWriter.hpp"
#include "details/MdInstrumentDefinitionOptionReader.hpp"
