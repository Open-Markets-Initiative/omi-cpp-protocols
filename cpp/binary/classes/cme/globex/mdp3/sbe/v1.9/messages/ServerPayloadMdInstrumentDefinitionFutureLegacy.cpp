#include "ServerPayloadMdInstrumentDefinitionFutureLegacy.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

ServerPayloadMdInstrumentDefinitionFutureLegacy::ServerPayloadMdInstrumentDefinitionFutureLegacy(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const MaturityMonthYear& maturity_month_year, const std::string& currency, const std::string& settl_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, Decimal min_price_increment, Decimal display_factor, std::optional<std::uint8_t> main_fraction, std::optional<std::uint8_t> sub_fraction, std::optional<std::uint8_t> price_display_format, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> trading_reference_price, const SettlPriceType& settl_price_type, std::optional<std::int32_t> open_interest_qty, std::optional<std::int32_t> cleared_volume, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::optional<std::int32_t> decay_quantity, std::optional<std::uint16_t> decay_start_date, std::optional<std::int32_t> original_contract_size, std::optional<std::int32_t> contract_multiplier, std::optional<std::int8_t> contract_multiplier_unit, std::optional<std::int8_t> flow_schedule_type, std::optional<Decimal> min_price_increment_amount, char user_defined_instrument, std::optional<std::uint16_t> trading_reference_date, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups)
  : match_event_indicator_(match_event_indicator), tot_num_reports_optional_(tot_num_reports_optional), security_update_action_(security_update_action), last_update_time_(last_update_time), md_security_trading_status_(md_security_trading_status), appl_id_(appl_id), market_segment_id_(market_segment_id), underlying_product_(underlying_product), security_exchange_(security_exchange), security_group_(security_group), asset_(asset), symbol_(symbol), security_id_(security_id), security_type_(security_type), cfi_code_(cfi_code), maturity_month_year_(maturity_month_year), currency_(currency), settl_currency_(settl_currency), match_algorithm_(match_algorithm), min_trade_vol_(min_trade_vol), max_trade_vol_(max_trade_vol), min_price_increment_(min_price_increment), display_factor_(display_factor), main_fraction_(main_fraction), sub_fraction_(sub_fraction), price_display_format_(price_display_format), unit_of_measure_(unit_of_measure), unit_of_measure_qty_(unit_of_measure_qty), trading_reference_price_(trading_reference_price), settl_price_type_(settl_price_type), open_interest_qty_(open_interest_qty), cleared_volume_(cleared_volume), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), decay_quantity_(decay_quantity), decay_start_date_(decay_start_date), original_contract_size_(original_contract_size), contract_multiplier_(contract_multiplier), contract_multiplier_unit_(contract_multiplier_unit), flow_schedule_type_(flow_schedule_type), min_price_increment_amount_(min_price_increment_amount), user_defined_instrument_(user_defined_instrument), trading_reference_date_(trading_reference_date), events_groups_(events_groups), feed_types_groups_(feed_types_groups), inst_attrib_groups_(inst_attrib_groups), lot_type_rules_groups_(lot_type_rules_groups) {}

const MatchEventIndicator& ServerPayloadMdInstrumentDefinitionFutureLegacy::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadMdInstrumentDefinitionFutureLegacy::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<std::uint32_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::tot_num_reports_optional() const { return tot_num_reports_optional_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_tot_num_reports_optional(std::optional<std::uint32_t> value) { tot_num_reports_optional_ = value; }

SecurityUpdateAction ServerPayloadMdInstrumentDefinitionFutureLegacy::security_update_action() const { return security_update_action_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_security_update_action(SecurityUpdateAction value) { security_update_action_ = value; }

std::chrono::nanoseconds ServerPayloadMdInstrumentDefinitionFutureLegacy::last_update_time() const { return last_update_time_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_last_update_time(std::chrono::nanoseconds value) { last_update_time_ = value; }

std::optional<MdSecurityTradingStatus> ServerPayloadMdInstrumentDefinitionFutureLegacy::md_security_trading_status() const { return md_security_trading_status_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value) { md_security_trading_status_ = value; }

std::int16_t ServerPayloadMdInstrumentDefinitionFutureLegacy::appl_id() const { return appl_id_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_appl_id(std::int16_t value) { appl_id_ = value; }

std::uint8_t ServerPayloadMdInstrumentDefinitionFutureLegacy::market_segment_id() const { return market_segment_id_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_market_segment_id(std::uint8_t value) { market_segment_id_ = value; }

std::uint8_t ServerPayloadMdInstrumentDefinitionFutureLegacy::underlying_product() const { return underlying_product_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_underlying_product(std::uint8_t value) { underlying_product_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::security_exchange() const { return security_exchange_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::security_exchange() { return security_exchange_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_security_exchange(const std::string& value) { security_exchange_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::security_group() const { return security_group_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::security_group() { return security_group_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_security_group(const std::string& value) { security_group_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::asset() const { return asset_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::asset() { return asset_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_asset(const std::string& value) { asset_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::symbol() const { return symbol_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::symbol() { return symbol_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_symbol(const std::string& value) { symbol_ = value; }

std::int32_t ServerPayloadMdInstrumentDefinitionFutureLegacy::security_id() const { return security_id_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_security_id(std::int32_t value) { security_id_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::security_type() const { return security_type_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::security_type() { return security_type_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_security_type(const std::string& value) { security_type_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::cfi_code() const { return cfi_code_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::cfi_code() { return cfi_code_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_cfi_code(const std::string& value) { cfi_code_ = value; }

const MaturityMonthYear& ServerPayloadMdInstrumentDefinitionFutureLegacy::maturity_month_year() const { return maturity_month_year_; }
MaturityMonthYear& ServerPayloadMdInstrumentDefinitionFutureLegacy::maturity_month_year() { return maturity_month_year_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_maturity_month_year(const MaturityMonthYear& value) { maturity_month_year_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::currency() const { return currency_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::currency() { return currency_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_currency(const std::string& value) { currency_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::settl_currency() const { return settl_currency_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::settl_currency() { return settl_currency_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_settl_currency(const std::string& value) { settl_currency_ = value; }

char ServerPayloadMdInstrumentDefinitionFutureLegacy::match_algorithm() const { return match_algorithm_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_match_algorithm(char value) { match_algorithm_ = value; }

std::uint32_t ServerPayloadMdInstrumentDefinitionFutureLegacy::min_trade_vol() const { return min_trade_vol_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_min_trade_vol(std::uint32_t value) { min_trade_vol_ = value; }

std::uint32_t ServerPayloadMdInstrumentDefinitionFutureLegacy::max_trade_vol() const { return max_trade_vol_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_max_trade_vol(std::uint32_t value) { max_trade_vol_ = value; }

Decimal ServerPayloadMdInstrumentDefinitionFutureLegacy::min_price_increment() const { return min_price_increment_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_min_price_increment(Decimal value) { min_price_increment_ = value; }

Decimal ServerPayloadMdInstrumentDefinitionFutureLegacy::display_factor() const { return display_factor_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_display_factor(Decimal value) { display_factor_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::main_fraction() const { return main_fraction_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_main_fraction(std::optional<std::uint8_t> value) { main_fraction_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::sub_fraction() const { return sub_fraction_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_sub_fraction(std::optional<std::uint8_t> value) { sub_fraction_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::price_display_format() const { return price_display_format_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_price_display_format(std::optional<std::uint8_t> value) { price_display_format_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::unit_of_measure() const { return unit_of_measure_; }
std::string& ServerPayloadMdInstrumentDefinitionFutureLegacy::unit_of_measure() { return unit_of_measure_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionFutureLegacy::unit_of_measure_qty() const { return unit_of_measure_qty_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_unit_of_measure_qty(std::optional<Decimal> value) { unit_of_measure_qty_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionFutureLegacy::trading_reference_price() const { return trading_reference_price_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_trading_reference_price(std::optional<Decimal> value) { trading_reference_price_ = value; }

const SettlPriceType& ServerPayloadMdInstrumentDefinitionFutureLegacy::settl_price_type() const { return settl_price_type_; }
SettlPriceType& ServerPayloadMdInstrumentDefinitionFutureLegacy::settl_price_type() { return settl_price_type_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_settl_price_type(const SettlPriceType& value) { settl_price_type_ = value; }

std::optional<std::int32_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::open_interest_qty() const { return open_interest_qty_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_open_interest_qty(std::optional<std::int32_t> value) { open_interest_qty_ = value; }

std::optional<std::int32_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::cleared_volume() const { return cleared_volume_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_cleared_volume(std::optional<std::int32_t> value) { cleared_volume_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionFutureLegacy::high_limit_price() const { return high_limit_price_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionFutureLegacy::low_limit_price() const { return low_limit_price_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionFutureLegacy::max_price_variation() const { return max_price_variation_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

std::optional<std::int32_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::decay_quantity() const { return decay_quantity_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_decay_quantity(std::optional<std::int32_t> value) { decay_quantity_ = value; }

std::optional<std::uint16_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::decay_start_date() const { return decay_start_date_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_decay_start_date(std::optional<std::uint16_t> value) { decay_start_date_ = value; }

std::optional<std::int32_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::original_contract_size() const { return original_contract_size_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_original_contract_size(std::optional<std::int32_t> value) { original_contract_size_ = value; }

std::optional<std::int32_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::contract_multiplier() const { return contract_multiplier_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_contract_multiplier(std::optional<std::int32_t> value) { contract_multiplier_ = value; }

std::optional<std::int8_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::contract_multiplier_unit() const { return contract_multiplier_unit_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_contract_multiplier_unit(std::optional<std::int8_t> value) { contract_multiplier_unit_ = value; }

std::optional<std::int8_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::flow_schedule_type() const { return flow_schedule_type_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_flow_schedule_type(std::optional<std::int8_t> value) { flow_schedule_type_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionFutureLegacy::min_price_increment_amount() const { return min_price_increment_amount_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_min_price_increment_amount(std::optional<Decimal> value) { min_price_increment_amount_ = value; }

char ServerPayloadMdInstrumentDefinitionFutureLegacy::user_defined_instrument() const { return user_defined_instrument_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_user_defined_instrument(char value) { user_defined_instrument_ = value; }

std::optional<std::uint16_t> ServerPayloadMdInstrumentDefinitionFutureLegacy::trading_reference_date() const { return trading_reference_date_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_trading_reference_date(std::optional<std::uint16_t> value) { trading_reference_date_ = value; }

const EventsGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::events_groups() const { return events_groups_; }
EventsGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::events_groups() { return events_groups_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_events_groups(const EventsGroups& value) { events_groups_ = value; }

const FeedTypesGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::feed_types_groups() const { return feed_types_groups_; }
FeedTypesGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::feed_types_groups() { return feed_types_groups_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_feed_types_groups(const FeedTypesGroups& value) { feed_types_groups_ = value; }

const InstAttribGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::inst_attrib_groups() const { return inst_attrib_groups_; }
InstAttribGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::inst_attrib_groups() { return inst_attrib_groups_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_inst_attrib_groups(const InstAttribGroups& value) { inst_attrib_groups_ = value; }

const LotTypeRulesGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::lot_type_rules_groups() const { return lot_type_rules_groups_; }
LotTypeRulesGroups& ServerPayloadMdInstrumentDefinitionFutureLegacy::lot_type_rules_groups() { return lot_type_rules_groups_; }
void ServerPayloadMdInstrumentDefinitionFutureLegacy::set_lot_type_rules_groups(const LotTypeRulesGroups& value) { lot_type_rules_groups_ = value; }

ServerTcpMessageCode ServerPayloadMdInstrumentDefinitionFutureLegacy::type() const { return message_type; }

std::string_view ServerPayloadMdInstrumentDefinitionFutureLegacy::name() const { return "Md Instrument Definition Future Legacy"; }

std::size_t ServerPayloadMdInstrumentDefinitionFutureLegacy::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    tot_num_reports_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    security_update_action_ = static_cast<SecurityUpdateAction>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    last_update_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    md_security_trading_status_ = wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 2, length);
    appl_id_ = wire::read_i16_le(data + offset);
    offset += 2;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    market_segment_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    underlying_product_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    security_exchange_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 6, length);
    security_group_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 6, length);
    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 20, length);
    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 6, length);
    security_type_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 6, length);
    cfi_code_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    offset += maturity_month_year_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 3, length);
    currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 3, length);
    settl_currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    match_algorithm_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    min_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    max_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    min_price_increment_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -7);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    display_factor_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -7);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    main_fraction_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    sub_fraction_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    price_display_format_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 30, length);
    unit_of_measure_ = wire::read_text(data + offset, 30, '\0');
    offset += 30;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    unit_of_measure_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    trading_reference_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    offset += settl_price_type_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    open_interest_qty_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    cleared_volume_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    decay_quantity_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 2, length);
    decay_start_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    original_contract_size_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 4, length);
    contract_multiplier_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(2147483647LL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    contract_multiplier_unit_ = wire::nullable(wire::read_i8(data + offset), static_cast<std::int8_t>(127LL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    flow_schedule_type_ = wire::nullable(wire::read_i8(data + offset), static_cast<std::int8_t>(127LL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 8, length);
    min_price_increment_amount_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -7);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 1, length);
    user_defined_instrument_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionFutureLegacy", offset + 2, length);
    trading_reference_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    offset += events_groups_.decode(data + offset, length - offset);

    offset += feed_types_groups_.decode(data + offset, length - offset);

    offset += inst_attrib_groups_.decode(data + offset, length - offset);

    offset += lot_type_rules_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadMdInstrumentDefinitionFutureLegacy::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadMdInstrumentDefinitionFutureLegacy", encoded_size(), capacity);

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

    wire::write_u8(data + offset, static_cast<std::uint8_t>(underlying_product_));
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

    wire::write_text(data + offset, 3, '\0', settl_currency_);
    offset += 3;

    wire::write_char(data + offset, match_algorithm_);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(min_trade_vol_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(max_trade_vol_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(min_price_increment_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(display_factor_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, main_fraction_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u8(data + offset, sub_fraction_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u8(data + offset, price_display_format_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_text(data + offset, 30, '\0', unit_of_measure_);
    offset += 30;

    wire::write_i64_le(data + offset, unit_of_measure_qty_ ? static_cast<std::int64_t>(unit_of_measure_qty_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, trading_reference_price_ ? static_cast<std::int64_t>(trading_reference_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    offset += settl_price_type_.encode(data + offset, capacity - offset);

    wire::write_i32_le(data + offset, open_interest_qty_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, cleared_volume_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ ? static_cast<std::int64_t>(max_price_variation_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, decay_quantity_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_u16_le(data + offset, decay_start_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_i32_le(data + offset, original_contract_size_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i32_le(data + offset, contract_multiplier_.value_or(static_cast<std::int32_t>(2147483647LL)));
    offset += 4;

    wire::write_i8(data + offset, contract_multiplier_unit_.value_or(static_cast<std::int8_t>(127LL)));
    offset += 1;

    wire::write_i8(data + offset, flow_schedule_type_.value_or(static_cast<std::int8_t>(127LL)));
    offset += 1;

    wire::write_i64_le(data + offset, min_price_increment_amount_ ? static_cast<std::int64_t>(min_price_increment_amount_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_char(data + offset, user_defined_instrument_);
    offset += 1;

    wire::write_u16_le(data + offset, trading_reference_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    offset += events_groups_.encode(data + offset, capacity - offset);

    offset += feed_types_groups_.encode(data + offset, capacity - offset);

    offset += inst_attrib_groups_.encode(data + offset, capacity - offset);

    offset += lot_type_rules_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadMdInstrumentDefinitionFutureLegacy::encoded_size() const {
    return match_event_indicator_.encoded_size() + 4 + 1 + 8 + 1 + 2 + 1 + 1 + 4 + 6 + 6 + 20 + 4 + 6 + 6 + maturity_month_year_.encoded_size() + 3 + 3 + 1 + 4 + 4 + 8 + 8 + 1 + 1 + 1 + 30 + 8 + 8 + settl_price_type_.encoded_size() + 4 + 4 + 8 + 8 + 8 + 4 + 2 + 4 + 4 + 1 + 1 + 8 + 1 + 2 + events_groups_.encoded_size() + feed_types_groups_.encoded_size() + inst_attrib_groups_.encoded_size() + lot_type_rules_groups_.encoded_size();
}

void ServerPayloadMdInstrumentDefinitionFutureLegacy::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadMdInstrumentDefinitionFutureLegacy::clone() const {
    return std::make_unique<ServerPayloadMdInstrumentDefinitionFutureLegacy>(*this);
}

void ServerPayloadMdInstrumentDefinitionFutureLegacy::print(std::ostream& out) const {
    out << "ServerPayloadMdInstrumentDefinitionFutureLegacy{";
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
    out << ", underlying_product=";
    out << static_cast<int>(underlying_product_);
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
    out << ", settl_currency=";
    print::text(out, settl_currency_);
    out << ", match_algorithm=";
    print::character(out, match_algorithm_);
    out << ", min_trade_vol=";
    out << min_trade_vol_;
    out << ", max_trade_vol=";
    out << max_trade_vol_;
    out << ", min_price_increment=";
    out << min_price_increment_;
    out << ", display_factor=";
    out << display_factor_;
    out << ", main_fraction=";
    print::optional(out, main_fraction_);
    out << ", sub_fraction=";
    print::optional(out, sub_fraction_);
    out << ", price_display_format=";
    print::optional(out, price_display_format_);
    out << ", unit_of_measure=";
    print::text(out, unit_of_measure_);
    out << ", unit_of_measure_qty=";
    print::optional(out, unit_of_measure_qty_);
    out << ", trading_reference_price=";
    print::optional(out, trading_reference_price_);
    out << ", settl_price_type=";
    settl_price_type_.print(out);
    out << ", open_interest_qty=";
    print::optional(out, open_interest_qty_);
    out << ", cleared_volume=";
    print::optional(out, cleared_volume_);
    out << ", high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", max_price_variation=";
    print::optional(out, max_price_variation_);
    out << ", decay_quantity=";
    print::optional(out, decay_quantity_);
    out << ", decay_start_date=";
    print::optional(out, decay_start_date_);
    out << ", original_contract_size=";
    print::optional(out, original_contract_size_);
    out << ", contract_multiplier=";
    print::optional(out, contract_multiplier_);
    out << ", contract_multiplier_unit=";
    print::optional(out, contract_multiplier_unit_);
    out << ", flow_schedule_type=";
    print::optional(out, flow_schedule_type_);
    out << ", min_price_increment_amount=";
    print::optional(out, min_price_increment_amount_);
    out << ", user_defined_instrument=";
    print::character(out, user_defined_instrument_);
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
    out << '}';
}

bool ServerPayloadMdInstrumentDefinitionFutureLegacy::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadMdInstrumentDefinitionFutureLegacy*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadMdInstrumentDefinitionFutureLegacy::operator==(const ServerPayloadMdInstrumentDefinitionFutureLegacy& other) const {
    return match_event_indicator_ == other.match_event_indicator_
        && tot_num_reports_optional_ == other.tot_num_reports_optional_
        && security_update_action_ == other.security_update_action_
        && last_update_time_ == other.last_update_time_
        && md_security_trading_status_ == other.md_security_trading_status_
        && appl_id_ == other.appl_id_
        && market_segment_id_ == other.market_segment_id_
        && underlying_product_ == other.underlying_product_
        && security_exchange_ == other.security_exchange_
        && security_group_ == other.security_group_
        && asset_ == other.asset_
        && symbol_ == other.symbol_
        && security_id_ == other.security_id_
        && security_type_ == other.security_type_
        && cfi_code_ == other.cfi_code_
        && maturity_month_year_ == other.maturity_month_year_
        && currency_ == other.currency_
        && settl_currency_ == other.settl_currency_
        && match_algorithm_ == other.match_algorithm_
        && min_trade_vol_ == other.min_trade_vol_
        && max_trade_vol_ == other.max_trade_vol_
        && min_price_increment_ == other.min_price_increment_
        && display_factor_ == other.display_factor_
        && main_fraction_ == other.main_fraction_
        && sub_fraction_ == other.sub_fraction_
        && price_display_format_ == other.price_display_format_
        && unit_of_measure_ == other.unit_of_measure_
        && unit_of_measure_qty_ == other.unit_of_measure_qty_
        && trading_reference_price_ == other.trading_reference_price_
        && settl_price_type_ == other.settl_price_type_
        && open_interest_qty_ == other.open_interest_qty_
        && cleared_volume_ == other.cleared_volume_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && decay_quantity_ == other.decay_quantity_
        && decay_start_date_ == other.decay_start_date_
        && original_contract_size_ == other.original_contract_size_
        && contract_multiplier_ == other.contract_multiplier_
        && contract_multiplier_unit_ == other.contract_multiplier_unit_
        && flow_schedule_type_ == other.flow_schedule_type_
        && min_price_increment_amount_ == other.min_price_increment_amount_
        && user_defined_instrument_ == other.user_defined_instrument_
        && trading_reference_date_ == other.trading_reference_date_
        && events_groups_ == other.events_groups_
        && feed_types_groups_ == other.feed_types_groups_
        && inst_attrib_groups_ == other.inst_attrib_groups_
        && lot_type_rules_groups_ == other.lot_type_rules_groups_;
}

bool ServerPayloadMdInstrumentDefinitionFutureLegacy::operator!=(const ServerPayloadMdInstrumentDefinitionFutureLegacy& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_9
