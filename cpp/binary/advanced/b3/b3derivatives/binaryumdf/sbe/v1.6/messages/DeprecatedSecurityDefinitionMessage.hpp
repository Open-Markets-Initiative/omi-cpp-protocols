#pragma once

#include <cstddef>
#include "../structs/FramingHeader.hpp"
#include "../structs/SbeGroupSupport.hpp"
#include "../types/SecurityId.hpp"
#include "../types/SecurityExchange.hpp"
#include "../types/SecurityIdSource.hpp"
#include "../types/SecurityGroup.hpp"
#include "../types/Symbol.hpp"
#include "../types/SecurityUpdateAction.hpp"
#include "../types/SecurityType.hpp"
#include "../types/SecuritySubType.hpp"
#include "../types/TotNoRelatedSym.hpp"
#include "../types/MinPriceIncrement.hpp"
#include "../types/StrikePrice.hpp"
#include "../types/ContractMultiplier.hpp"
#include "../types/PriceDivisor.hpp"
#include "../types/SecurityValidityTimestamp.hpp"
#include "../types/NoSharesIssued.hpp"
#include "../types/ClearingHouseId.hpp"
#include "../types/MinOrderQty.hpp"
#include "../types/MaxOrderQty.hpp"
#include "../types/MinLotSize.hpp"
#include "../types/MinTradeVol.hpp"
#include "../types/CorporateActionEventId.hpp"
#include "../types/IssueDate.hpp"
#include "../types/MaturityDate.hpp"
#include "../types/CountryOfIssue.hpp"
#include "../types/StartDate.hpp"
#include "../types/EndDate.hpp"
#include "../types/SettlType.hpp"
#include "../types/SettlDate.hpp"
#include "../types/DatedDate.hpp"
#include "../types/IsinNumber.hpp"
#include "../types/Asset.hpp"
#include "../types/CfiCode.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../structs/ContractSettlMonth.hpp"
#include "../types/Currency.hpp"
#include "../types/StrikeCurrency.hpp"
#include "../types/SettlCurrency.hpp"
#include "../types/SecurityStrategyType.hpp"
#include "../types/LotType.hpp"
#include "../types/TickSizeDenominator.hpp"
#include "../types/Product.hpp"
#include "../types/ExerciseStyle.hpp"
#include "../types/PutOrCall.hpp"
#include "../types/PriceType.hpp"
#include "../types/MarketSegmentId.hpp"
#include "../types/GovernanceIndicator.hpp"
#include "../types/SecurityMatchType.hpp"
#include "../types/LastFragment.hpp"
#include "../types/MultiLegModel.hpp"
#include "../types/MultiLegPriceMethod.hpp"
#include "../types/MinCrossQty.hpp"
#include "../types/UnderlyingSecurityId.hpp"
#include "../types/IndexPct.hpp"
#include "../types/IndexTheoreticalQty.hpp"
#include "../types/UnderlyingSymbol.hpp"
#include "../structs/GroupSizeEncoding.hpp"
#include "../types/LegSecurityId.hpp"
#include "../types/LegRatioQty.hpp"
#include "../types/LegSecurityType.hpp"
#include "../types/LegSide.hpp"
#include "../types/LegSymbol.hpp"
#include "../types/InstrAttribType.hpp"
#include "../types/InstrAttribValue.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

namespace sbe_binaryumdf = ::b3::b3derivatives::binaryumdf::sbe::v1_6;

#pragma pack(push, 1)
struct deprecated_security_definition_message_deprecated_underlyings_groups_entry {
    sbe_binaryumdf::underlying_security_id underlying_security_id;
    sbe_binaryumdf::index_pct index_pct;
    sbe_binaryumdf::index_theoretical_qty index_theoretical_qty;
    sbe_binaryumdf::underlying_symbol underlying_symbol;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct deprecated_security_definition_message_deprecated_legs_groups_entry {
    sbe_binaryumdf::leg_security_id leg_security_id;
    sbe_binaryumdf::leg_ratio_qty leg_ratio_qty;
    sbe_binaryumdf::leg_security_type leg_security_type;
    sbe_binaryumdf::leg_side leg_side;
    sbe_binaryumdf::leg_symbol leg_symbol;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct deprecated_security_definition_message_deprecated_instr_attribs_groups_entry {
    sbe_binaryumdf::instr_attrib_type instr_attrib_type;
    sbe_binaryumdf::instr_attrib_value instr_attrib_value;
};
#pragma pack(pop)


#pragma pack(push, 1)

// Deprecated Security Definition Message
struct deprecated_security_definition_message {

    struct fields_type {
        sbe_binaryumdf::security_id security_id;
        sbe_binaryumdf::security_exchange security_exchange;
        sbe_binaryumdf::security_id_source security_id_source;
        sbe_binaryumdf::security_group security_group;
        sbe_binaryumdf::symbol symbol;
        sbe_binaryumdf::security_update_action security_update_action;
        sbe_binaryumdf::security_type security_type;
        sbe_binaryumdf::security_sub_type security_sub_type;
        sbe_binaryumdf::tot_no_related_sym tot_no_related_sym;
        sbe_binaryumdf::min_price_increment min_price_increment;
        sbe_binaryumdf::strike_price strike_price;
        sbe_binaryumdf::contract_multiplier contract_multiplier;
        sbe_binaryumdf::price_divisor price_divisor;
        sbe_binaryumdf::security_validity_timestamp security_validity_timestamp;
        sbe_binaryumdf::no_shares_issued no_shares_issued;
        sbe_binaryumdf::clearing_house_id clearing_house_id;
        sbe_binaryumdf::min_order_qty min_order_qty;
        sbe_binaryumdf::max_order_qty max_order_qty;
        sbe_binaryumdf::min_lot_size min_lot_size;
        sbe_binaryumdf::min_trade_vol min_trade_vol;
        sbe_binaryumdf::corporate_action_event_id corporate_action_event_id;
        sbe_binaryumdf::issue_date issue_date;
        sbe_binaryumdf::maturity_date maturity_date;
        sbe_binaryumdf::country_of_issue country_of_issue;
        sbe_binaryumdf::start_date start_date;
        sbe_binaryumdf::end_date end_date;
        sbe_binaryumdf::settl_type settl_type;
        sbe_binaryumdf::settl_date settl_date;
        sbe_binaryumdf::dated_date dated_date;
        sbe_binaryumdf::isin_number isin_number;
        sbe_binaryumdf::asset asset;
        sbe_binaryumdf::cfi_code cfi_code;
        sbe_binaryumdf::maturity_month_year maturity_month_year;
        sbe_binaryumdf::contract_settl_month contract_settl_month;
        sbe_binaryumdf::currency currency;
        sbe_binaryumdf::strike_currency strike_currency;
        sbe_binaryumdf::settl_currency settl_currency;
        sbe_binaryumdf::security_strategy_type security_strategy_type;
        sbe_binaryumdf::lot_type lot_type;
        sbe_binaryumdf::tick_size_denominator tick_size_denominator;
        sbe_binaryumdf::product product;
        sbe_binaryumdf::exercise_style exercise_style;
        sbe_binaryumdf::put_or_call put_or_call;
        sbe_binaryumdf::price_type price_type;
        sbe_binaryumdf::market_segment_id market_segment_id;
        sbe_binaryumdf::governance_indicator governance_indicator;
        sbe_binaryumdf::security_match_type security_match_type;
        sbe_binaryumdf::last_fragment last_fragment;
        sbe_binaryumdf::multi_leg_model multi_leg_model;
        sbe_binaryumdf::multi_leg_price_method multi_leg_price_method;
        sbe_binaryumdf::min_cross_qty min_cross_qty;
    };

    sbe_binaryumdf::framing_header header = {std::uint16_t(sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)), {}};
    sbe_binaryumdf::message_header message_header;

    static constexpr std::size_t max_message_size = 1280;
    static constexpr std::size_t tail_capacity = max_message_size - sizeof(sbe_binaryumdf::framing_header) - sizeof(fields_type) - sizeof(sbe_binaryumdf::message_header);

    fields_type fields;
    std::byte tail[tail_capacity];

    // tail buffer accessors
    const std::byte* tail_begin() const { return tail; }
    const std::byte* tail_end() const {
        auto sz = header.message_length.get().value();
        return sz == sizeof(sbe_binaryumdf::framing_header) + sizeof(fields_type) + sizeof(sbe_binaryumdf::message_header)
            ? tail + tail_capacity
            : tail + (sz - sizeof(sbe_binaryumdf::framing_header) - sizeof(fields_type) - sizeof(sbe_binaryumdf::message_header));
    }

    // sequential access to variable-length regions
    sbe_group_iterator<deprecated_security_definition_message_deprecated_underlyings_groups_entry, group_size_encoding> deprecated_underlyings_groups() const {
        return { tail_begin(), tail_end() };
    }

    sbe_group_iterator<deprecated_security_definition_message_deprecated_legs_groups_entry, group_size_encoding> deprecated_legs_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_group_iterator<deprecated_security_definition_message_deprecated_instr_attribs_groups_entry, group_size_encoding> deprecated_instr_attribs_groups(const std::byte* position) const {
        return { position, tail_end() };
    }

    sbe_var_data security_desc(const std::byte* position) const {
        return { position, tail_end() };
    }


    // parse method
    static deprecated_security_definition_message* parse(std::byte* buffer) {
        return reinterpret_cast<deprecated_security_definition_message*>(buffer);
    }

    // parse method const
    static const deprecated_security_definition_message* parse(const std::byte* buffer) {
        return reinterpret_cast<const deprecated_security_definition_message*>(buffer);
    }

};

// layout verification
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_id) == 0, "unexpected offset of deprecated_security_definition_message::fields_type::security_id");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_exchange) == 8, "unexpected offset of deprecated_security_definition_message::fields_type::security_exchange");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_id_source) == 12, "unexpected offset of deprecated_security_definition_message::fields_type::security_id_source");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_group) == 13, "unexpected offset of deprecated_security_definition_message::fields_type::security_group");
static_assert(offsetof(deprecated_security_definition_message::fields_type, symbol) == 16, "unexpected offset of deprecated_security_definition_message::fields_type::symbol");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_update_action) == 36, "unexpected offset of deprecated_security_definition_message::fields_type::security_update_action");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_type) == 37, "unexpected offset of deprecated_security_definition_message::fields_type::security_type");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_sub_type) == 38, "unexpected offset of deprecated_security_definition_message::fields_type::security_sub_type");
static_assert(offsetof(deprecated_security_definition_message::fields_type, tot_no_related_sym) == 40, "unexpected offset of deprecated_security_definition_message::fields_type::tot_no_related_sym");
static_assert(offsetof(deprecated_security_definition_message::fields_type, min_price_increment) == 44, "unexpected offset of deprecated_security_definition_message::fields_type::min_price_increment");
static_assert(offsetof(deprecated_security_definition_message::fields_type, strike_price) == 52, "unexpected offset of deprecated_security_definition_message::fields_type::strike_price");
static_assert(offsetof(deprecated_security_definition_message::fields_type, contract_multiplier) == 60, "unexpected offset of deprecated_security_definition_message::fields_type::contract_multiplier");
static_assert(offsetof(deprecated_security_definition_message::fields_type, price_divisor) == 68, "unexpected offset of deprecated_security_definition_message::fields_type::price_divisor");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_validity_timestamp) == 76, "unexpected offset of deprecated_security_definition_message::fields_type::security_validity_timestamp");
static_assert(offsetof(deprecated_security_definition_message::fields_type, no_shares_issued) == 84, "unexpected offset of deprecated_security_definition_message::fields_type::no_shares_issued");
static_assert(offsetof(deprecated_security_definition_message::fields_type, clearing_house_id) == 92, "unexpected offset of deprecated_security_definition_message::fields_type::clearing_house_id");
static_assert(offsetof(deprecated_security_definition_message::fields_type, min_order_qty) == 100, "unexpected offset of deprecated_security_definition_message::fields_type::min_order_qty");
static_assert(offsetof(deprecated_security_definition_message::fields_type, max_order_qty) == 108, "unexpected offset of deprecated_security_definition_message::fields_type::max_order_qty");
static_assert(offsetof(deprecated_security_definition_message::fields_type, min_lot_size) == 116, "unexpected offset of deprecated_security_definition_message::fields_type::min_lot_size");
static_assert(offsetof(deprecated_security_definition_message::fields_type, min_trade_vol) == 124, "unexpected offset of deprecated_security_definition_message::fields_type::min_trade_vol");
static_assert(offsetof(deprecated_security_definition_message::fields_type, corporate_action_event_id) == 132, "unexpected offset of deprecated_security_definition_message::fields_type::corporate_action_event_id");
static_assert(offsetof(deprecated_security_definition_message::fields_type, issue_date) == 136, "unexpected offset of deprecated_security_definition_message::fields_type::issue_date");
static_assert(offsetof(deprecated_security_definition_message::fields_type, maturity_date) == 140, "unexpected offset of deprecated_security_definition_message::fields_type::maturity_date");
static_assert(offsetof(deprecated_security_definition_message::fields_type, country_of_issue) == 144, "unexpected offset of deprecated_security_definition_message::fields_type::country_of_issue");
static_assert(offsetof(deprecated_security_definition_message::fields_type, start_date) == 146, "unexpected offset of deprecated_security_definition_message::fields_type::start_date");
static_assert(offsetof(deprecated_security_definition_message::fields_type, end_date) == 150, "unexpected offset of deprecated_security_definition_message::fields_type::end_date");
static_assert(offsetof(deprecated_security_definition_message::fields_type, settl_type) == 154, "unexpected offset of deprecated_security_definition_message::fields_type::settl_type");
static_assert(offsetof(deprecated_security_definition_message::fields_type, settl_date) == 156, "unexpected offset of deprecated_security_definition_message::fields_type::settl_date");
static_assert(offsetof(deprecated_security_definition_message::fields_type, dated_date) == 160, "unexpected offset of deprecated_security_definition_message::fields_type::dated_date");
static_assert(offsetof(deprecated_security_definition_message::fields_type, isin_number) == 164, "unexpected offset of deprecated_security_definition_message::fields_type::isin_number");
static_assert(offsetof(deprecated_security_definition_message::fields_type, asset) == 176, "unexpected offset of deprecated_security_definition_message::fields_type::asset");
static_assert(offsetof(deprecated_security_definition_message::fields_type, cfi_code) == 182, "unexpected offset of deprecated_security_definition_message::fields_type::cfi_code");
static_assert(offsetof(deprecated_security_definition_message::fields_type, maturity_month_year) == 188, "unexpected offset of deprecated_security_definition_message::fields_type::maturity_month_year");
static_assert(offsetof(deprecated_security_definition_message::fields_type, contract_settl_month) == 193, "unexpected offset of deprecated_security_definition_message::fields_type::contract_settl_month");
static_assert(offsetof(deprecated_security_definition_message::fields_type, currency) == 198, "unexpected offset of deprecated_security_definition_message::fields_type::currency");
static_assert(offsetof(deprecated_security_definition_message::fields_type, strike_currency) == 201, "unexpected offset of deprecated_security_definition_message::fields_type::strike_currency");
static_assert(offsetof(deprecated_security_definition_message::fields_type, settl_currency) == 204, "unexpected offset of deprecated_security_definition_message::fields_type::settl_currency");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_strategy_type) == 207, "unexpected offset of deprecated_security_definition_message::fields_type::security_strategy_type");
static_assert(offsetof(deprecated_security_definition_message::fields_type, lot_type) == 210, "unexpected offset of deprecated_security_definition_message::fields_type::lot_type");
static_assert(offsetof(deprecated_security_definition_message::fields_type, tick_size_denominator) == 211, "unexpected offset of deprecated_security_definition_message::fields_type::tick_size_denominator");
static_assert(offsetof(deprecated_security_definition_message::fields_type, product) == 212, "unexpected offset of deprecated_security_definition_message::fields_type::product");
static_assert(offsetof(deprecated_security_definition_message::fields_type, exercise_style) == 213, "unexpected offset of deprecated_security_definition_message::fields_type::exercise_style");
static_assert(offsetof(deprecated_security_definition_message::fields_type, put_or_call) == 214, "unexpected offset of deprecated_security_definition_message::fields_type::put_or_call");
static_assert(offsetof(deprecated_security_definition_message::fields_type, price_type) == 215, "unexpected offset of deprecated_security_definition_message::fields_type::price_type");
static_assert(offsetof(deprecated_security_definition_message::fields_type, market_segment_id) == 216, "unexpected offset of deprecated_security_definition_message::fields_type::market_segment_id");
static_assert(offsetof(deprecated_security_definition_message::fields_type, governance_indicator) == 217, "unexpected offset of deprecated_security_definition_message::fields_type::governance_indicator");
static_assert(offsetof(deprecated_security_definition_message::fields_type, security_match_type) == 218, "unexpected offset of deprecated_security_definition_message::fields_type::security_match_type");
static_assert(offsetof(deprecated_security_definition_message::fields_type, last_fragment) == 219, "unexpected offset of deprecated_security_definition_message::fields_type::last_fragment");
static_assert(offsetof(deprecated_security_definition_message::fields_type, multi_leg_model) == 220, "unexpected offset of deprecated_security_definition_message::fields_type::multi_leg_model");
static_assert(offsetof(deprecated_security_definition_message::fields_type, multi_leg_price_method) == 221, "unexpected offset of deprecated_security_definition_message::fields_type::multi_leg_price_method");
static_assert(offsetof(deprecated_security_definition_message::fields_type, min_cross_qty) == 222, "unexpected offset of deprecated_security_definition_message::fields_type::min_cross_qty");
static_assert(sizeof(deprecated_security_definition_message::fields_type) == 230, "unexpected sizeof deprecated_security_definition_message::fields_type");

#pragma pack(pop)
}

#include "details/DeprecatedSecurityDefinitionMessageWriter.hpp"
#include "details/DeprecatedSecurityDefinitionMessageReader.hpp"
