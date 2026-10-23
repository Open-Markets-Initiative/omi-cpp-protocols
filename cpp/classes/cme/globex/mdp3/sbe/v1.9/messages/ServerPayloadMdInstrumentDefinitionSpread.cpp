#include "ServerPayloadMdInstrumentDefinitionSpread.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ServerPayloadMdInstrumentDefinitionSpread::ServerPayloadMdInstrumentDefinitionSpread(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::optional<std::uint8_t> underlying_product_optional, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const MaturityMonthYear& maturity_month_year, const std::string& currency, const std::string& security_sub_type, char user_defined_instrument, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, std::optional<Decimal> min_price_increment_optional_ex, Decimal display_factor_ex, std::optional<std::uint8_t> price_display_format, std::optional<Decimal> price_ratio_ex, std::optional<std::int8_t> tick_rule, const std::string& unit_of_measure, std::optional<Decimal> trading_reference_price_ex, const SettlPriceType& settl_price_type, std::optional<std::int32_t> open_interest_qty, std::optional<std::int32_t> cleared_volume, std::optional<Decimal> high_limit_price_ex, std::optional<Decimal> low_limit_price_ex, std::optional<Decimal> max_price_variation_ex, std::optional<std::uint8_t> main_fraction, std::optional<std::uint8_t> sub_fraction, std::optional<std::uint16_t> trading_reference_date, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups, const LegsGroups& legs_groups)
  : match_event_indicator_(match_event_indicator), tot_num_reports_optional_(tot_num_reports_optional), security_update_action_(security_update_action), last_update_time_(last_update_time), md_security_trading_status_(md_security_trading_status), appl_id_(appl_id), market_segment_id_(market_segment_id), underlying_product_optional_(underlying_product_optional), security_exchange_(security_exchange), security_group_(security_group), asset_(asset), symbol_(symbol), security_id_(security_id), security_type_(security_type), cfi_code_(cfi_code), maturity_month_year_(maturity_month_year), currency_(currency), security_sub_type_(security_sub_type), user_defined_instrument_(user_defined_instrument), match_algorithm_(match_algorithm), min_trade_vol_(min_trade_vol), max_trade_vol_(max_trade_vol), min_price_increment_optional_ex_(min_price_increment_optional_ex), display_factor_ex_(display_factor_ex), price_display_format_(price_display_format), price_ratio_ex_(price_ratio_ex), tick_rule_(tick_rule), unit_of_measure_(unit_of_measure), trading_reference_price_ex_(trading_reference_price_ex), settl_price_type_(settl_price_type), open_interest_qty_(open_interest_qty), cleared_volume_(cleared_volume), high_limit_price_ex_(high_limit_price_ex), low_limit_price_ex_(low_limit_price_ex), max_price_variation_ex_(max_price_variation_ex), main_fraction_(main_fraction), sub_fraction_(sub_fraction), trading_reference_date_(trading_reference_date), events_groups_(events_groups), feed_types_groups_(feed_types_groups), inst_attrib_groups_(inst_attrib_groups), lot_type_rules_groups_(lot_type_rules_groups), legs_groups_(legs_groups) {}

const MatchEventIndicator& ServerPayloadMdInstrumentDefinitionSpread::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadMdInstrumentDefinitionSpread::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<std::uint32_t> ServerPayloadMdInstrumentDefinitionSpread::tot_num_reports_optional() const { return tot_num_reports_optional_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_tot_num_reports_optional(std::optional<std::uint32_t> value) { tot_num_reports_optional_ = value; }

SecurityUpdateAction ServerPayloadMdInstrumentDefinitionSpread::security_update_action() const { return security_update_action_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_security_update_action(SecurityUpdateAction value) { security_update_action_ = value; }

std::chrono::nanoseconds ServerPayloadMdInstrumentDefinitionSpread::last_update_time() const { return last_update_time_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_last_update_time(std::chrono::nanoseconds value) { last_update_time_ = value; }

std::optional<MdSecurityTradingStatus> ServerPayloadMdInstrumentDefinitionSpread::md_security_trading_status() const { return md_security_trading_status_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value) { md_security_trading_status_ = value; }

std::int16_t ServerPayloadMdInstrumentDefinitionSpread::appl_id() const { return appl_id_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_appl_id(std::int16_t value) { appl_id_ = value; }

std::uint8_t ServerPayloadMdInstrumentDefinitionSpread::market_segment_id() const { return market_segment_id_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_market_segment_id(std::uint8_t value) { market_segment_id_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionSpread::underlying_product_optional() const { return underlying_product_optional_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_underlying_product_optional(std::optional<std::uint8_t> value) { underlying_product_optional_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::security_exchange() const { return security_exchange_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::security_exchange() { return security_exchange_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_security_exchange(const std::string& value) { security_exchange_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::security_group() const { return security_group_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::security_group() { return security_group_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_security_group(const std::string& value) { security_group_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::asset() const { return asset_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::asset() { return asset_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_asset(const std::string& value) { asset_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::symbol() const { return symbol_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::symbol() { return symbol_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_symbol(const std::string& value) { symbol_ = value; }

std::int32_t ServerPayloadMdInstrumentDefinitionSpread::security_id() const { return security_id_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_security_id(std::int32_t value) { security_id_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::security_type() const { return security_type_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::security_type() { return security_type_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_security_type(const std::string& value) { security_type_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::cfi_code() const { return cfi_code_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::cfi_code() { return cfi_code_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_cfi_code(const std::string& value) { cfi_code_ = value; }

const MaturityMonthYear& ServerPayloadMdInstrumentDefinitionSpread::maturity_month_year() const { return maturity_month_year_; }
MaturityMonthYear& ServerPayloadMdInstrumentDefinitionSpread::maturity_month_year() { return maturity_month_year_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_maturity_month_year(const MaturityMonthYear& value) { maturity_month_year_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::currency() const { return currency_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::currency() { return currency_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_currency(const std::string& value) { currency_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::security_sub_type() const { return security_sub_type_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::security_sub_type() { return security_sub_type_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_security_sub_type(const std::string& value) { security_sub_type_ = value; }

char ServerPayloadMdInstrumentDefinitionSpread::user_defined_instrument() const { return user_defined_instrument_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_user_defined_instrument(char value) { user_defined_instrument_ = value; }

char ServerPayloadMdInstrumentDefinitionSpread::match_algorithm() const { return match_algorithm_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_match_algorithm(char value) { match_algorithm_ = value; }

std::uint32_t ServerPayloadMdInstrumentDefinitionSpread::min_trade_vol() const { return min_trade_vol_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_min_trade_vol(std::uint32_t value) { min_trade_vol_ = value; }

std::uint32_t ServerPayloadMdInstrumentDefinitionSpread::max_trade_vol() const { return max_trade_vol_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_max_trade_vol(std::uint32_t value) { max_trade_vol_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionSpread::min_price_increment_optional_ex() const { return min_price_increment_optional_ex_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_min_price_increment_optional_ex(std::optional<Decimal> value) { min_price_increment_optional_ex_ = value; }

Decimal ServerPayloadMdInstrumentDefinitionSpread::display_factor_ex() const { return display_factor_ex_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_display_factor_ex(Decimal value) { display_factor_ex_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionSpread::price_display_format() const { return price_display_format_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_price_display_format(std::optional<std::uint8_t> value) { price_display_format_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionSpread::price_ratio_ex() const { return price_ratio_ex_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_price_ratio_ex(std::optional<Decimal> value) { price_ratio_ex_ = value; }

std::optional<std::int8_t> ServerPayloadMdInstrumentDefinitionSpread::tick_rule() const { return tick_rule_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_tick_rule(std::optional<std::int8_t> value) { tick_rule_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionSpread::unit_of_measure() const { return unit_of_measure_; }
std::string& ServerPayloadMdInstrumentDefinitionSpread::unit_of_measure() { return unit_of_measure_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionSpread::trading_reference_price_ex() const { return trading_reference_price_ex_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_trading_reference_price_ex(std::optional<Decimal> value) { trading_reference_price_ex_ = value; }

const SettlPriceType& ServerPayloadMdInstrumentDefinitionSpread::settl_price_type() const { return settl_price_type_; }
SettlPriceType& ServerPayloadMdInstrumentDefinitionSpread::settl_price_type() { return settl_price_type_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_settl_price_type(const SettlPriceType& value) { settl_price_type_ = value; }

std::optional<std::int32_t> ServerPayloadMdInstrumentDefinitionSpread::open_interest_qty() const { return open_interest_qty_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_open_interest_qty(std::optional<std::int32_t> value) { open_interest_qty_ = value; }

std::optional<std::int32_t> ServerPayloadMdInstrumentDefinitionSpread::cleared_volume() const { return cleared_volume_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_cleared_volume(std::optional<std::int32_t> value) { cleared_volume_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionSpread::high_limit_price_ex() const { return high_limit_price_ex_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_high_limit_price_ex(std::optional<Decimal> value) { high_limit_price_ex_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionSpread::low_limit_price_ex() const { return low_limit_price_ex_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_low_limit_price_ex(std::optional<Decimal> value) { low_limit_price_ex_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionSpread::max_price_variation_ex() const { return max_price_variation_ex_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_max_price_variation_ex(std::optional<Decimal> value) { max_price_variation_ex_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionSpread::main_fraction() const { return main_fraction_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_main_fraction(std::optional<std::uint8_t> value) { main_fraction_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionSpread::sub_fraction() const { return sub_fraction_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_sub_fraction(std::optional<std::uint8_t> value) { sub_fraction_ = value; }

std::optional<std::uint16_t> ServerPayloadMdInstrumentDefinitionSpread::trading_reference_date() const { return trading_reference_date_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_trading_reference_date(std::optional<std::uint16_t> value) { trading_reference_date_ = value; }

const EventsGroups& ServerPayloadMdInstrumentDefinitionSpread::events_groups() const { return events_groups_; }
EventsGroups& ServerPayloadMdInstrumentDefinitionSpread::events_groups() { return events_groups_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_events_groups(const EventsGroups& value) { events_groups_ = value; }

const FeedTypesGroups& ServerPayloadMdInstrumentDefinitionSpread::feed_types_groups() const { return feed_types_groups_; }
FeedTypesGroups& ServerPayloadMdInstrumentDefinitionSpread::feed_types_groups() { return feed_types_groups_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_feed_types_groups(const FeedTypesGroups& value) { feed_types_groups_ = value; }

const InstAttribGroups& ServerPayloadMdInstrumentDefinitionSpread::inst_attrib_groups() const { return inst_attrib_groups_; }
InstAttribGroups& ServerPayloadMdInstrumentDefinitionSpread::inst_attrib_groups() { return inst_attrib_groups_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_inst_attrib_groups(const InstAttribGroups& value) { inst_attrib_groups_ = value; }

const LotTypeRulesGroups& ServerPayloadMdInstrumentDefinitionSpread::lot_type_rules_groups() const { return lot_type_rules_groups_; }
LotTypeRulesGroups& ServerPayloadMdInstrumentDefinitionSpread::lot_type_rules_groups() { return lot_type_rules_groups_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_lot_type_rules_groups(const LotTypeRulesGroups& value) { lot_type_rules_groups_ = value; }

const LegsGroups& ServerPayloadMdInstrumentDefinitionSpread::legs_groups() const { return legs_groups_; }
LegsGroups& ServerPayloadMdInstrumentDefinitionSpread::legs_groups() { return legs_groups_; }
void ServerPayloadMdInstrumentDefinitionSpread::set_legs_groups(const LegsGroups& value) { legs_groups_ = value; }

ServerTcpMessageCode ServerPayloadMdInstrumentDefinitionSpread::type() const { return message_type; }

std::string_view ServerPayloadMdInstrumentDefinitionSpread::name() const { return "Md Instrument Definition Spread"; }

std::size_t ServerPayloadMdInstrumentDefinitionSpread::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 4, length);
    tot_num_reports_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    security_update_action_ = static_cast<SecurityUpdateAction>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    last_update_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    md_security_trading_status_ = wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 2, length);
    appl_id_ = wire::read_i16_le(data + offset);
    offset += 2;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    market_segment_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    underlying_product_optional_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 4, length);
    security_exchange_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 6, length);
    security_group_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 6, length);
    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 20, length);
    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 6, length);
    security_type_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 6, length);
    cfi_code_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    offset += maturity_month_year_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 3, length);
    currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 5, length);
    security_sub_type_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    user_defined_instrument_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    match_algorithm_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 4, length);
    min_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 4, length);
    max_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    min_price_increment_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    display_factor_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    price_display_format_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    price_ratio_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    tick_rule_ = wire::nullable(wire::read_i8(data + offset), static_cast<std::int8_t>(127LL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 30, length);
    unit_of_measure_ = wire::read_text(data + offset, 30, '\0');
    offset += 30;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    trading_reference_price_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    offset += settl_price_type_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 4, length);
    open_interest_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 4, length);
    cleared_volume_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    high_limit_price_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    low_limit_price_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 8, length);
    max_price_variation_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    main_fraction_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 1, length);
    sub_fraction_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionSpread", offset + 2, length);
    trading_reference_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    offset += events_groups_.decode(data + offset, length - offset);

    offset += feed_types_groups_.decode(data + offset, length - offset);

    offset += inst_attrib_groups_.decode(data + offset, length - offset);

    offset += lot_type_rules_groups_.decode(data + offset, length - offset);

    offset += legs_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadMdInstrumentDefinitionSpread::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadMdInstrumentDefinitionSpread", encoded_size(), capacity);

    offset += match_event_indicator_.encode(data + offset, capacity - offset);

    wire::write_u32_le(data + offset, tot_num_reports_optional_.value_or(static_cast<std::uint32_t>(4294967295ULL)));
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(security_update_action_));
    offset += 1;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(last_update_time_.count()));
    offset += 8;

    wire::write_u8(data + offset, md_security_trading_status_ ? static_cast<std::uint8_t>(*md_security_trading_status_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_i16_le(data + offset, static_cast<std::int16_t>(appl_id_));
    offset += 2;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(market_segment_id_));
    offset += 1;

    wire::write_u8(data + offset, underlying_product_optional_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_text(data + offset, 4, '\0', security_exchange_);
    offset += 4;

    wire::write_text(data + offset, 6, '\0', security_group_);
    offset += 6;

    wire::write_text(data + offset, 6, '\0', asset_);
    offset += 6;

    wire::write_text(data + offset, 20, '\0', symbol_);
    offset += 20;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(security_id_));
    offset += 4;

    wire::write_text(data + offset, 6, '\0', security_type_);
    offset += 6;

    wire::write_text(data + offset, 6, '\0', cfi_code_);
    offset += 6;

    offset += maturity_month_year_.encode(data + offset, capacity - offset);

    wire::write_text(data + offset, 3, '\0', currency_);
    offset += 3;

    wire::write_text(data + offset, 5, '\0', security_sub_type_);
    offset += 5;

    wire::write_char(data + offset, user_defined_instrument_);
    offset += 1;

    wire::write_char(data + offset, match_algorithm_);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(min_trade_vol_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(max_trade_vol_));
    offset += 4;

    wire::write_i64_le(data + offset, min_price_increment_optional_ex_ ? static_cast<std::int64_t>(min_price_increment_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(display_factor_ex_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, price_display_format_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_i64_le(data + offset, price_ratio_ex_ ? static_cast<std::int64_t>(price_ratio_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i8(data + offset, tick_rule_.value_or(static_cast<std::int8_t>(127LL)));
    offset += 1;

    wire::write_text(data + offset, 30, '\0', unit_of_measure_);
    offset += 30;

    wire::write_i64_le(data + offset, trading_reference_price_ex_ ? static_cast<std::int64_t>(trading_reference_price_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    offset += settl_price_type_.encode(data + offset, capacity - offset);

    wire::write_i32_le(data + offset, open_interest_qty_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, cleared_volume_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i64_le(data + offset, high_limit_price_ex_ ? static_cast<std::int64_t>(high_limit_price_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ex_ ? static_cast<std::int64_t>(low_limit_price_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ex_ ? static_cast<std::int64_t>(max_price_variation_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u8(data + offset, main_fraction_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u8(data + offset, sub_fraction_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u16_le(data + offset, trading_reference_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    offset += events_groups_.encode(data + offset, capacity - offset);

    offset += feed_types_groups_.encode(data + offset, capacity - offset);

    offset += inst_attrib_groups_.encode(data + offset, capacity - offset);

    offset += lot_type_rules_groups_.encode(data + offset, capacity - offset);

    offset += legs_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadMdInstrumentDefinitionSpread::encoded_size() const {
    return match_event_indicator_.encoded_size() + 4 + 1 + 8 + 1 + 2 + 1 + 1 + 4 + 6 + 6 + 20 + 4 + 6 + 6 + maturity_month_year_.encoded_size() + 3 + 5 + 1 + 1 + 4 + 4 + 8 + 8 + 1 + 8 + 1 + 30 + 8 + settl_price_type_.encoded_size() + 4 + 4 + 8 + 8 + 8 + 1 + 1 + 2 + events_groups_.encoded_size() + feed_types_groups_.encoded_size() + inst_attrib_groups_.encoded_size() + lot_type_rules_groups_.encoded_size() + legs_groups_.encoded_size();
}

void ServerPayloadMdInstrumentDefinitionSpread::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadMdInstrumentDefinitionSpread::clone() const {
    return std::make_unique<ServerPayloadMdInstrumentDefinitionSpread>(*this);
}

void ServerPayloadMdInstrumentDefinitionSpread::print(std::ostream& out) const {
    out << "ServerPayloadMdInstrumentDefinitionSpread{";
    out << "match_event_indicator=";
    match_event_indicator_.print(out);
    out << ", tot_num_reports_optional=";
    print::optional(out, tot_num_reports_optional_);
    out << ", security_update_action=";
    out << security_update_action_;
    out << ", last_update_time=";
    out << last_update_time_.count();
    out << ", md_security_trading_status=";
    print::optional(out, md_security_trading_status_);
    out << ", appl_id=";
    out << appl_id_;
    out << ", market_segment_id=";
    out << static_cast<int>(market_segment_id_);
    out << ", underlying_product_optional=";
    print::optional(out, underlying_product_optional_);
    out << ", security_exchange=";
    print::text(out, security_exchange_);
    out << ", security_group=";
    print::text(out, security_group_);
    out << ", asset=";
    print::text(out, asset_);
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", security_id=";
    out << security_id_;
    out << ", security_type=";
    print::text(out, security_type_);
    out << ", cfi_code=";
    print::text(out, cfi_code_);
    out << ", maturity_month_year=";
    maturity_month_year_.print(out);
    out << ", currency=";
    print::text(out, currency_);
    out << ", security_sub_type=";
    print::text(out, security_sub_type_);
    out << ", user_defined_instrument=";
    print::character(out, user_defined_instrument_);
    out << ", match_algorithm=";
    print::character(out, match_algorithm_);
    out << ", min_trade_vol=";
    out << min_trade_vol_;
    out << ", max_trade_vol=";
    out << max_trade_vol_;
    out << ", min_price_increment_optional_ex=";
    print::optional(out, min_price_increment_optional_ex_);
    out << ", display_factor_ex=";
    out << display_factor_ex_;
    out << ", price_display_format=";
    print::optional(out, price_display_format_);
    out << ", price_ratio_ex=";
    print::optional(out, price_ratio_ex_);
    out << ", tick_rule=";
    print::optional(out, tick_rule_);
    out << ", unit_of_measure=";
    print::text(out, unit_of_measure_);
    out << ", trading_reference_price_ex=";
    print::optional(out, trading_reference_price_ex_);
    out << ", settl_price_type=";
    settl_price_type_.print(out);
    out << ", open_interest_qty=";
    print::optional(out, open_interest_qty_);
    out << ", cleared_volume=";
    print::optional(out, cleared_volume_);
    out << ", high_limit_price_ex=";
    print::optional(out, high_limit_price_ex_);
    out << ", low_limit_price_ex=";
    print::optional(out, low_limit_price_ex_);
    out << ", max_price_variation_ex=";
    print::optional(out, max_price_variation_ex_);
    out << ", main_fraction=";
    print::optional(out, main_fraction_);
    out << ", sub_fraction=";
    print::optional(out, sub_fraction_);
    out << ", trading_reference_date=";
    print::optional(out, trading_reference_date_);
    out << ", events_groups=";
    events_groups_.print(out);
    out << ", feed_types_groups=";
    feed_types_groups_.print(out);
    out << ", inst_attrib_groups=";
    inst_attrib_groups_.print(out);
    out << ", lot_type_rules_groups=";
    lot_type_rules_groups_.print(out);
    out << ", legs_groups=";
    legs_groups_.print(out);
    out << '}';
}

bool ServerPayloadMdInstrumentDefinitionSpread::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadMdInstrumentDefinitionSpread*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadMdInstrumentDefinitionSpread::operator==(const ServerPayloadMdInstrumentDefinitionSpread& other) const {
    return match_event_indicator_ == other.match_event_indicator_
        && tot_num_reports_optional_ == other.tot_num_reports_optional_
        && security_update_action_ == other.security_update_action_
        && last_update_time_ == other.last_update_time_
        && md_security_trading_status_ == other.md_security_trading_status_
        && appl_id_ == other.appl_id_
        && market_segment_id_ == other.market_segment_id_
        && underlying_product_optional_ == other.underlying_product_optional_
        && security_exchange_ == other.security_exchange_
        && security_group_ == other.security_group_
        && asset_ == other.asset_
        && symbol_ == other.symbol_
        && security_id_ == other.security_id_
        && security_type_ == other.security_type_
        && cfi_code_ == other.cfi_code_
        && maturity_month_year_ == other.maturity_month_year_
        && currency_ == other.currency_
        && security_sub_type_ == other.security_sub_type_
        && user_defined_instrument_ == other.user_defined_instrument_
        && match_algorithm_ == other.match_algorithm_
        && min_trade_vol_ == other.min_trade_vol_
        && max_trade_vol_ == other.max_trade_vol_
        && min_price_increment_optional_ex_ == other.min_price_increment_optional_ex_
        && display_factor_ex_ == other.display_factor_ex_
        && price_display_format_ == other.price_display_format_
        && price_ratio_ex_ == other.price_ratio_ex_
        && tick_rule_ == other.tick_rule_
        && unit_of_measure_ == other.unit_of_measure_
        && trading_reference_price_ex_ == other.trading_reference_price_ex_
        && settl_price_type_ == other.settl_price_type_
        && open_interest_qty_ == other.open_interest_qty_
        && cleared_volume_ == other.cleared_volume_
        && high_limit_price_ex_ == other.high_limit_price_ex_
        && low_limit_price_ex_ == other.low_limit_price_ex_
        && max_price_variation_ex_ == other.max_price_variation_ex_
        && main_fraction_ == other.main_fraction_
        && sub_fraction_ == other.sub_fraction_
        && trading_reference_date_ == other.trading_reference_date_
        && events_groups_ == other.events_groups_
        && feed_types_groups_ == other.feed_types_groups_
        && inst_attrib_groups_ == other.inst_attrib_groups_
        && lot_type_rules_groups_ == other.lot_type_rules_groups_
        && legs_groups_ == other.legs_groups_;
}

bool ServerPayloadMdInstrumentDefinitionSpread::operator!=(const ServerPayloadMdInstrumentDefinitionSpread& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
