#include "InstrumentDefMsg.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

InstrumentDefMsg::InstrumentDefMsg(std::optional<std::chrono::nanoseconds> ts_recv, std::optional<Decimal> min_price_increment, std::optional<Decimal> display_factor, std::optional<std::chrono::nanoseconds> expiration, std::optional<std::chrono::nanoseconds> activation, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> min_price_increment_amount, std::optional<Decimal> price_ratio, std::optional<Decimal> strike_price, std::uint64_t raw_instrument_id, std::optional<Decimal> leg_price, std::optional<Decimal> leg_delta, std::int32_t inst_attrib_value, std::uint32_t underlying_id, std::int32_t market_depth_implied, std::int32_t market_depth, std::uint32_t market_segment_id, std::uint32_t max_trade_vol, std::int32_t min_lot_size, std::int32_t min_lot_size_block, std::int32_t min_lot_size_round_lot, std::uint32_t min_trade_vol, std::int32_t contract_multiplier, std::int32_t decay_quantity, std::int32_t original_contract_size, std::uint32_t leg_instrument_id, std::int32_t leg_ratio_price_numerator, std::int32_t leg_ratio_price_denominator, std::int32_t leg_ratio_qty_numerator, std::int32_t leg_ratio_qty_denominator, std::uint32_t leg_underlying_id, std::int16_t appl_id, std::uint16_t maturity_year, std::uint16_t decay_start_date, std::uint16_t channel, std::uint16_t leg_count, std::uint16_t leg_index, const std::string& currency, const std::string& settl_currency, const std::string& secsubtype, const std::string& raw_symbol, const std::string& group, const std::string& exchange, const std::string& asset, const std::string& cfi, const std::string& security_type, const std::string& unit_of_measure, const std::string& underlying, const std::string& strike_price_currency, const std::string& leg_raw_symbol, InstrumentClass instrument_class, MatchAlgorithm match_algorithm, std::uint8_t main_fraction, std::uint8_t price_display_format, std::uint8_t sub_fraction, std::uint8_t underlying_product, SecurityUpdateAction security_update_action, std::uint8_t maturity_month, std::uint8_t maturity_day, std::uint8_t maturity_week, UserDefinedInstrument user_defined_instrument, std::int8_t contract_multiplier_unit, std::int8_t flow_schedule_type, std::uint8_t tick_rule, LegInstrumentClass leg_instrument_class, LegSide leg_side, const std::array<std::byte, 17>& reserved_17)
  : ts_recv_(ts_recv), min_price_increment_(min_price_increment), display_factor_(display_factor), expiration_(expiration), activation_(activation), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), unit_of_measure_qty_(unit_of_measure_qty), min_price_increment_amount_(min_price_increment_amount), price_ratio_(price_ratio), strike_price_(strike_price), raw_instrument_id_(raw_instrument_id), leg_price_(leg_price), leg_delta_(leg_delta), inst_attrib_value_(inst_attrib_value), underlying_id_(underlying_id), market_depth_implied_(market_depth_implied), market_depth_(market_depth), market_segment_id_(market_segment_id), max_trade_vol_(max_trade_vol), min_lot_size_(min_lot_size), min_lot_size_block_(min_lot_size_block), min_lot_size_round_lot_(min_lot_size_round_lot), min_trade_vol_(min_trade_vol), contract_multiplier_(contract_multiplier), decay_quantity_(decay_quantity), original_contract_size_(original_contract_size), leg_instrument_id_(leg_instrument_id), leg_ratio_price_numerator_(leg_ratio_price_numerator), leg_ratio_price_denominator_(leg_ratio_price_denominator), leg_ratio_qty_numerator_(leg_ratio_qty_numerator), leg_ratio_qty_denominator_(leg_ratio_qty_denominator), leg_underlying_id_(leg_underlying_id), appl_id_(appl_id), maturity_year_(maturity_year), decay_start_date_(decay_start_date), channel_(channel), leg_count_(leg_count), leg_index_(leg_index), currency_(currency), settl_currency_(settl_currency), secsubtype_(secsubtype), raw_symbol_(raw_symbol), group_(group), exchange_(exchange), asset_(asset), cfi_(cfi), security_type_(security_type), unit_of_measure_(unit_of_measure), underlying_(underlying), strike_price_currency_(strike_price_currency), leg_raw_symbol_(leg_raw_symbol), instrument_class_(instrument_class), match_algorithm_(match_algorithm), main_fraction_(main_fraction), price_display_format_(price_display_format), sub_fraction_(sub_fraction), underlying_product_(underlying_product), security_update_action_(security_update_action), maturity_month_(maturity_month), maturity_day_(maturity_day), maturity_week_(maturity_week), user_defined_instrument_(user_defined_instrument), contract_multiplier_unit_(contract_multiplier_unit), flow_schedule_type_(flow_schedule_type), tick_rule_(tick_rule), leg_instrument_class_(leg_instrument_class), leg_side_(leg_side), reserved_17_(reserved_17) {}

std::optional<std::chrono::nanoseconds> InstrumentDefMsg::ts_recv() const { return ts_recv_; }
void InstrumentDefMsg::set_ts_recv(std::optional<std::chrono::nanoseconds> value) { ts_recv_ = value; }

std::optional<Decimal> InstrumentDefMsg::min_price_increment() const { return min_price_increment_; }
void InstrumentDefMsg::set_min_price_increment(std::optional<Decimal> value) { min_price_increment_ = value; }

std::optional<Decimal> InstrumentDefMsg::display_factor() const { return display_factor_; }
void InstrumentDefMsg::set_display_factor(std::optional<Decimal> value) { display_factor_ = value; }

std::optional<std::chrono::nanoseconds> InstrumentDefMsg::expiration() const { return expiration_; }
void InstrumentDefMsg::set_expiration(std::optional<std::chrono::nanoseconds> value) { expiration_ = value; }

std::optional<std::chrono::nanoseconds> InstrumentDefMsg::activation() const { return activation_; }
void InstrumentDefMsg::set_activation(std::optional<std::chrono::nanoseconds> value) { activation_ = value; }

std::optional<Decimal> InstrumentDefMsg::high_limit_price() const { return high_limit_price_; }
void InstrumentDefMsg::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> InstrumentDefMsg::low_limit_price() const { return low_limit_price_; }
void InstrumentDefMsg::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> InstrumentDefMsg::max_price_variation() const { return max_price_variation_; }
void InstrumentDefMsg::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

std::optional<Decimal> InstrumentDefMsg::unit_of_measure_qty() const { return unit_of_measure_qty_; }
void InstrumentDefMsg::set_unit_of_measure_qty(std::optional<Decimal> value) { unit_of_measure_qty_ = value; }

std::optional<Decimal> InstrumentDefMsg::min_price_increment_amount() const { return min_price_increment_amount_; }
void InstrumentDefMsg::set_min_price_increment_amount(std::optional<Decimal> value) { min_price_increment_amount_ = value; }

std::optional<Decimal> InstrumentDefMsg::price_ratio() const { return price_ratio_; }
void InstrumentDefMsg::set_price_ratio(std::optional<Decimal> value) { price_ratio_ = value; }

std::optional<Decimal> InstrumentDefMsg::strike_price() const { return strike_price_; }
void InstrumentDefMsg::set_strike_price(std::optional<Decimal> value) { strike_price_ = value; }

std::uint64_t InstrumentDefMsg::raw_instrument_id() const { return raw_instrument_id_; }
void InstrumentDefMsg::set_raw_instrument_id(std::uint64_t value) { raw_instrument_id_ = value; }

std::optional<Decimal> InstrumentDefMsg::leg_price() const { return leg_price_; }
void InstrumentDefMsg::set_leg_price(std::optional<Decimal> value) { leg_price_ = value; }

std::optional<Decimal> InstrumentDefMsg::leg_delta() const { return leg_delta_; }
void InstrumentDefMsg::set_leg_delta(std::optional<Decimal> value) { leg_delta_ = value; }

std::int32_t InstrumentDefMsg::inst_attrib_value() const { return inst_attrib_value_; }
void InstrumentDefMsg::set_inst_attrib_value(std::int32_t value) { inst_attrib_value_ = value; }

std::uint32_t InstrumentDefMsg::underlying_id() const { return underlying_id_; }
void InstrumentDefMsg::set_underlying_id(std::uint32_t value) { underlying_id_ = value; }

std::int32_t InstrumentDefMsg::market_depth_implied() const { return market_depth_implied_; }
void InstrumentDefMsg::set_market_depth_implied(std::int32_t value) { market_depth_implied_ = value; }

std::int32_t InstrumentDefMsg::market_depth() const { return market_depth_; }
void InstrumentDefMsg::set_market_depth(std::int32_t value) { market_depth_ = value; }

std::uint32_t InstrumentDefMsg::market_segment_id() const { return market_segment_id_; }
void InstrumentDefMsg::set_market_segment_id(std::uint32_t value) { market_segment_id_ = value; }

std::uint32_t InstrumentDefMsg::max_trade_vol() const { return max_trade_vol_; }
void InstrumentDefMsg::set_max_trade_vol(std::uint32_t value) { max_trade_vol_ = value; }

std::int32_t InstrumentDefMsg::min_lot_size() const { return min_lot_size_; }
void InstrumentDefMsg::set_min_lot_size(std::int32_t value) { min_lot_size_ = value; }

std::int32_t InstrumentDefMsg::min_lot_size_block() const { return min_lot_size_block_; }
void InstrumentDefMsg::set_min_lot_size_block(std::int32_t value) { min_lot_size_block_ = value; }

std::int32_t InstrumentDefMsg::min_lot_size_round_lot() const { return min_lot_size_round_lot_; }
void InstrumentDefMsg::set_min_lot_size_round_lot(std::int32_t value) { min_lot_size_round_lot_ = value; }

std::uint32_t InstrumentDefMsg::min_trade_vol() const { return min_trade_vol_; }
void InstrumentDefMsg::set_min_trade_vol(std::uint32_t value) { min_trade_vol_ = value; }

std::int32_t InstrumentDefMsg::contract_multiplier() const { return contract_multiplier_; }
void InstrumentDefMsg::set_contract_multiplier(std::int32_t value) { contract_multiplier_ = value; }

std::int32_t InstrumentDefMsg::decay_quantity() const { return decay_quantity_; }
void InstrumentDefMsg::set_decay_quantity(std::int32_t value) { decay_quantity_ = value; }

std::int32_t InstrumentDefMsg::original_contract_size() const { return original_contract_size_; }
void InstrumentDefMsg::set_original_contract_size(std::int32_t value) { original_contract_size_ = value; }

std::uint32_t InstrumentDefMsg::leg_instrument_id() const { return leg_instrument_id_; }
void InstrumentDefMsg::set_leg_instrument_id(std::uint32_t value) { leg_instrument_id_ = value; }

std::int32_t InstrumentDefMsg::leg_ratio_price_numerator() const { return leg_ratio_price_numerator_; }
void InstrumentDefMsg::set_leg_ratio_price_numerator(std::int32_t value) { leg_ratio_price_numerator_ = value; }

std::int32_t InstrumentDefMsg::leg_ratio_price_denominator() const { return leg_ratio_price_denominator_; }
void InstrumentDefMsg::set_leg_ratio_price_denominator(std::int32_t value) { leg_ratio_price_denominator_ = value; }

std::int32_t InstrumentDefMsg::leg_ratio_qty_numerator() const { return leg_ratio_qty_numerator_; }
void InstrumentDefMsg::set_leg_ratio_qty_numerator(std::int32_t value) { leg_ratio_qty_numerator_ = value; }

std::int32_t InstrumentDefMsg::leg_ratio_qty_denominator() const { return leg_ratio_qty_denominator_; }
void InstrumentDefMsg::set_leg_ratio_qty_denominator(std::int32_t value) { leg_ratio_qty_denominator_ = value; }

std::uint32_t InstrumentDefMsg::leg_underlying_id() const { return leg_underlying_id_; }
void InstrumentDefMsg::set_leg_underlying_id(std::uint32_t value) { leg_underlying_id_ = value; }

std::int16_t InstrumentDefMsg::appl_id() const { return appl_id_; }
void InstrumentDefMsg::set_appl_id(std::int16_t value) { appl_id_ = value; }

std::uint16_t InstrumentDefMsg::maturity_year() const { return maturity_year_; }
void InstrumentDefMsg::set_maturity_year(std::uint16_t value) { maturity_year_ = value; }

std::uint16_t InstrumentDefMsg::decay_start_date() const { return decay_start_date_; }
void InstrumentDefMsg::set_decay_start_date(std::uint16_t value) { decay_start_date_ = value; }

std::uint16_t InstrumentDefMsg::channel() const { return channel_; }
void InstrumentDefMsg::set_channel(std::uint16_t value) { channel_ = value; }

std::uint16_t InstrumentDefMsg::leg_count() const { return leg_count_; }
void InstrumentDefMsg::set_leg_count(std::uint16_t value) { leg_count_ = value; }

std::uint16_t InstrumentDefMsg::leg_index() const { return leg_index_; }
void InstrumentDefMsg::set_leg_index(std::uint16_t value) { leg_index_ = value; }

const std::string& InstrumentDefMsg::currency() const { return currency_; }
std::string& InstrumentDefMsg::currency() { return currency_; }
void InstrumentDefMsg::set_currency(const std::string& value) { currency_ = value; }

const std::string& InstrumentDefMsg::settl_currency() const { return settl_currency_; }
std::string& InstrumentDefMsg::settl_currency() { return settl_currency_; }
void InstrumentDefMsg::set_settl_currency(const std::string& value) { settl_currency_ = value; }

const std::string& InstrumentDefMsg::secsubtype() const { return secsubtype_; }
std::string& InstrumentDefMsg::secsubtype() { return secsubtype_; }
void InstrumentDefMsg::set_secsubtype(const std::string& value) { secsubtype_ = value; }

const std::string& InstrumentDefMsg::raw_symbol() const { return raw_symbol_; }
std::string& InstrumentDefMsg::raw_symbol() { return raw_symbol_; }
void InstrumentDefMsg::set_raw_symbol(const std::string& value) { raw_symbol_ = value; }

const std::string& InstrumentDefMsg::group() const { return group_; }
std::string& InstrumentDefMsg::group() { return group_; }
void InstrumentDefMsg::set_group(const std::string& value) { group_ = value; }

const std::string& InstrumentDefMsg::exchange() const { return exchange_; }
std::string& InstrumentDefMsg::exchange() { return exchange_; }
void InstrumentDefMsg::set_exchange(const std::string& value) { exchange_ = value; }

const std::string& InstrumentDefMsg::asset() const { return asset_; }
std::string& InstrumentDefMsg::asset() { return asset_; }
void InstrumentDefMsg::set_asset(const std::string& value) { asset_ = value; }

const std::string& InstrumentDefMsg::cfi() const { return cfi_; }
std::string& InstrumentDefMsg::cfi() { return cfi_; }
void InstrumentDefMsg::set_cfi(const std::string& value) { cfi_ = value; }

const std::string& InstrumentDefMsg::security_type() const { return security_type_; }
std::string& InstrumentDefMsg::security_type() { return security_type_; }
void InstrumentDefMsg::set_security_type(const std::string& value) { security_type_ = value; }

const std::string& InstrumentDefMsg::unit_of_measure() const { return unit_of_measure_; }
std::string& InstrumentDefMsg::unit_of_measure() { return unit_of_measure_; }
void InstrumentDefMsg::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

const std::string& InstrumentDefMsg::underlying() const { return underlying_; }
std::string& InstrumentDefMsg::underlying() { return underlying_; }
void InstrumentDefMsg::set_underlying(const std::string& value) { underlying_ = value; }

const std::string& InstrumentDefMsg::strike_price_currency() const { return strike_price_currency_; }
std::string& InstrumentDefMsg::strike_price_currency() { return strike_price_currency_; }
void InstrumentDefMsg::set_strike_price_currency(const std::string& value) { strike_price_currency_ = value; }

const std::string& InstrumentDefMsg::leg_raw_symbol() const { return leg_raw_symbol_; }
std::string& InstrumentDefMsg::leg_raw_symbol() { return leg_raw_symbol_; }
void InstrumentDefMsg::set_leg_raw_symbol(const std::string& value) { leg_raw_symbol_ = value; }

InstrumentClass InstrumentDefMsg::instrument_class() const { return instrument_class_; }
void InstrumentDefMsg::set_instrument_class(InstrumentClass value) { instrument_class_ = value; }

MatchAlgorithm InstrumentDefMsg::match_algorithm() const { return match_algorithm_; }
void InstrumentDefMsg::set_match_algorithm(MatchAlgorithm value) { match_algorithm_ = value; }

std::uint8_t InstrumentDefMsg::main_fraction() const { return main_fraction_; }
void InstrumentDefMsg::set_main_fraction(std::uint8_t value) { main_fraction_ = value; }

std::uint8_t InstrumentDefMsg::price_display_format() const { return price_display_format_; }
void InstrumentDefMsg::set_price_display_format(std::uint8_t value) { price_display_format_ = value; }

std::uint8_t InstrumentDefMsg::sub_fraction() const { return sub_fraction_; }
void InstrumentDefMsg::set_sub_fraction(std::uint8_t value) { sub_fraction_ = value; }

std::uint8_t InstrumentDefMsg::underlying_product() const { return underlying_product_; }
void InstrumentDefMsg::set_underlying_product(std::uint8_t value) { underlying_product_ = value; }

SecurityUpdateAction InstrumentDefMsg::security_update_action() const { return security_update_action_; }
void InstrumentDefMsg::set_security_update_action(SecurityUpdateAction value) { security_update_action_ = value; }

std::uint8_t InstrumentDefMsg::maturity_month() const { return maturity_month_; }
void InstrumentDefMsg::set_maturity_month(std::uint8_t value) { maturity_month_ = value; }

std::uint8_t InstrumentDefMsg::maturity_day() const { return maturity_day_; }
void InstrumentDefMsg::set_maturity_day(std::uint8_t value) { maturity_day_ = value; }

std::uint8_t InstrumentDefMsg::maturity_week() const { return maturity_week_; }
void InstrumentDefMsg::set_maturity_week(std::uint8_t value) { maturity_week_ = value; }

UserDefinedInstrument InstrumentDefMsg::user_defined_instrument() const { return user_defined_instrument_; }
void InstrumentDefMsg::set_user_defined_instrument(UserDefinedInstrument value) { user_defined_instrument_ = value; }

std::int8_t InstrumentDefMsg::contract_multiplier_unit() const { return contract_multiplier_unit_; }
void InstrumentDefMsg::set_contract_multiplier_unit(std::int8_t value) { contract_multiplier_unit_ = value; }

std::int8_t InstrumentDefMsg::flow_schedule_type() const { return flow_schedule_type_; }
void InstrumentDefMsg::set_flow_schedule_type(std::int8_t value) { flow_schedule_type_ = value; }

std::uint8_t InstrumentDefMsg::tick_rule() const { return tick_rule_; }
void InstrumentDefMsg::set_tick_rule(std::uint8_t value) { tick_rule_ = value; }

LegInstrumentClass InstrumentDefMsg::leg_instrument_class() const { return leg_instrument_class_; }
void InstrumentDefMsg::set_leg_instrument_class(LegInstrumentClass value) { leg_instrument_class_ = value; }

LegSide InstrumentDefMsg::leg_side() const { return leg_side_; }
void InstrumentDefMsg::set_leg_side(LegSide value) { leg_side_ = value; }

const std::array<std::byte, 17>& InstrumentDefMsg::reserved_17() const { return reserved_17_; }
std::array<std::byte, 17>& InstrumentDefMsg::reserved_17() { return reserved_17_; }
void InstrumentDefMsg::set_reserved_17(const std::array<std::byte, 17>& value) { reserved_17_ = value; }

MessageCode InstrumentDefMsg::type() const { return message_type; }

std::string_view InstrumentDefMsg::name() const { return "Instrument Def Msg"; }

std::size_t InstrumentDefMsg::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;
    wire::require("InstrumentDefMsg", wire_size, length);

    ts_recv_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    min_price_increment_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    display_factor_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    expiration_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    activation_ = wire::nullable_duration<std::chrono::nanoseconds>(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    unit_of_measure_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    min_price_increment_amount_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    price_ratio_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    strike_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    raw_instrument_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    leg_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    leg_delta_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    inst_attrib_value_ = wire::read_i32_le(data + offset);
    offset += 4;

    underlying_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    market_depth_implied_ = wire::read_i32_le(data + offset);
    offset += 4;

    market_depth_ = wire::read_i32_le(data + offset);
    offset += 4;

    market_segment_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    max_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    min_lot_size_ = wire::read_i32_le(data + offset);
    offset += 4;

    min_lot_size_block_ = wire::read_i32_le(data + offset);
    offset += 4;

    min_lot_size_round_lot_ = wire::read_i32_le(data + offset);
    offset += 4;

    min_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    contract_multiplier_ = wire::read_i32_le(data + offset);
    offset += 4;

    decay_quantity_ = wire::read_i32_le(data + offset);
    offset += 4;

    original_contract_size_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_instrument_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    leg_ratio_price_numerator_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_ratio_price_denominator_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_ratio_qty_numerator_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_ratio_qty_denominator_ = wire::read_i32_le(data + offset);
    offset += 4;

    leg_underlying_id_ = wire::read_u32_le(data + offset);
    offset += 4;

    appl_id_ = wire::read_i16_le(data + offset);
    offset += 2;

    maturity_year_ = wire::read_u16_le(data + offset);
    offset += 2;

    decay_start_date_ = wire::read_u16_le(data + offset);
    offset += 2;

    channel_ = wire::read_u16_le(data + offset);
    offset += 2;

    leg_count_ = wire::read_u16_le(data + offset);
    offset += 2;

    leg_index_ = wire::read_u16_le(data + offset);
    offset += 2;

    currency_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    settl_currency_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    secsubtype_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    raw_symbol_ = wire::read_text(data + offset, 71, '\0');
    offset += 71;

    group_ = wire::read_text(data + offset, 21, '\0');
    offset += 21;

    exchange_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    asset_ = wire::read_text(data + offset, 11, '\0');
    offset += 11;

    cfi_ = wire::read_text(data + offset, 7, '\0');
    offset += 7;

    security_type_ = wire::read_text(data + offset, 7, '\0');
    offset += 7;

    unit_of_measure_ = wire::read_text(data + offset, 31, '\0');
    offset += 31;

    underlying_ = wire::read_text(data + offset, 21, '\0');
    offset += 21;

    strike_price_currency_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    leg_raw_symbol_ = wire::read_text(data + offset, 71, '\0');
    offset += 71;

    instrument_class_ = static_cast<InstrumentClass>(wire::read_char(data + offset));
    offset += 1;

    match_algorithm_ = static_cast<MatchAlgorithm>(wire::read_char(data + offset));
    offset += 1;

    main_fraction_ = wire::read_u8(data + offset);
    offset += 1;

    price_display_format_ = wire::read_u8(data + offset);
    offset += 1;

    sub_fraction_ = wire::read_u8(data + offset);
    offset += 1;

    underlying_product_ = wire::read_u8(data + offset);
    offset += 1;

    security_update_action_ = static_cast<SecurityUpdateAction>(wire::read_char(data + offset));
    offset += 1;

    maturity_month_ = wire::read_u8(data + offset);
    offset += 1;

    maturity_day_ = wire::read_u8(data + offset);
    offset += 1;

    maturity_week_ = wire::read_u8(data + offset);
    offset += 1;

    user_defined_instrument_ = static_cast<UserDefinedInstrument>(wire::read_char(data + offset));
    offset += 1;

    contract_multiplier_unit_ = wire::read_i8(data + offset);
    offset += 1;

    flow_schedule_type_ = wire::read_i8(data + offset);
    offset += 1;

    tick_rule_ = wire::read_u8(data + offset);
    offset += 1;

    leg_instrument_class_ = static_cast<LegInstrumentClass>(wire::read_char(data + offset));
    offset += 1;

    leg_side_ = static_cast<LegSide>(wire::read_char(data + offset));
    offset += 1;

    wire::read_bytes(data + offset, reserved_17_.data(), 17);
    offset += 17;

    return offset;
}

std::size_t InstrumentDefMsg::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("InstrumentDefMsg", wire_size, capacity);

    wire::write_u64_le(data + offset, ts_recv_ ? static_cast<std::uint64_t>(ts_recv_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i64_le(data + offset, min_price_increment_ ? static_cast<std::int64_t>(min_price_increment_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, display_factor_ ? static_cast<std::int64_t>(display_factor_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u64_le(data + offset, expiration_ ? static_cast<std::uint64_t>(expiration_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_u64_le(data + offset, activation_ ? static_cast<std::uint64_t>(activation_->count()) : static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ ? static_cast<std::int64_t>(max_price_variation_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, unit_of_measure_qty_ ? static_cast<std::int64_t>(unit_of_measure_qty_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, min_price_increment_amount_ ? static_cast<std::int64_t>(min_price_increment_amount_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, price_ratio_ ? static_cast<std::int64_t>(price_ratio_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, strike_price_ ? static_cast<std::int64_t>(strike_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(raw_instrument_id_));
    offset += 8;

    wire::write_i64_le(data + offset, leg_price_ ? static_cast<std::int64_t>(leg_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, leg_delta_ ? static_cast<std::int64_t>(leg_delta_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(inst_attrib_value_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(underlying_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(market_depth_implied_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(market_depth_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(market_segment_id_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(max_trade_vol_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(min_lot_size_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(min_lot_size_block_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(min_lot_size_round_lot_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(min_trade_vol_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(contract_multiplier_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(decay_quantity_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(original_contract_size_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(leg_instrument_id_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_ratio_price_numerator_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_ratio_price_denominator_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_ratio_qty_numerator_));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(leg_ratio_qty_denominator_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(leg_underlying_id_));
    offset += 4;

    wire::write_i16_le(data + offset, static_cast<std::int16_t>(appl_id_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(maturity_year_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(decay_start_date_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(channel_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(leg_count_));
    offset += 2;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(leg_index_));
    offset += 2;

    wire::write_text(data + offset, 4, '\0', currency_);
    offset += 4;

    wire::write_text(data + offset, 4, '\0', settl_currency_);
    offset += 4;

    wire::write_text(data + offset, 6, '\0', secsubtype_);
    offset += 6;

    wire::write_text(data + offset, 71, '\0', raw_symbol_);
    offset += 71;

    wire::write_text(data + offset, 21, '\0', group_);
    offset += 21;

    wire::write_text(data + offset, 5, '\0', exchange_);
    offset += 5;

    wire::write_text(data + offset, 11, '\0', asset_);
    offset += 11;

    wire::write_text(data + offset, 7, '\0', cfi_);
    offset += 7;

    wire::write_text(data + offset, 7, '\0', security_type_);
    offset += 7;

    wire::write_text(data + offset, 31, '\0', unit_of_measure_);
    offset += 31;

    wire::write_text(data + offset, 21, '\0', underlying_);
    offset += 21;

    wire::write_text(data + offset, 4, '\0', strike_price_currency_);
    offset += 4;

    wire::write_text(data + offset, 71, '\0', leg_raw_symbol_);
    offset += 71;

    wire::write_char(data + offset, static_cast<char>(instrument_class_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(match_algorithm_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(main_fraction_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_display_format_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(sub_fraction_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(underlying_product_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(security_update_action_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(maturity_month_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(maturity_day_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(maturity_week_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(user_defined_instrument_));
    offset += 1;

    wire::write_i8(data + offset, static_cast<std::int8_t>(contract_multiplier_unit_));
    offset += 1;

    wire::write_i8(data + offset, static_cast<std::int8_t>(flow_schedule_type_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(tick_rule_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(leg_instrument_class_));
    offset += 1;

    wire::write_char(data + offset, static_cast<char>(leg_side_));
    offset += 1;

    wire::write_bytes(data + offset, reserved_17_.data(), 17);
    offset += 17;

    return offset;
}

std::size_t InstrumentDefMsg::encoded_size() const {
    return wire_size;
}

void InstrumentDefMsg::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> InstrumentDefMsg::clone() const {
    return std::make_unique<InstrumentDefMsg>(*this);
}

void InstrumentDefMsg::print(std::ostream& out) const {
    out << "InstrumentDefMsg{";
    out << "ts_recv=";
    print::optional_duration(out, ts_recv_);
    out << ", min_price_increment=";
    print::optional(out, min_price_increment_);
    out << ", display_factor=";
    print::optional(out, display_factor_);
    out << ", expiration=";
    print::optional_duration(out, expiration_);
    out << ", activation=";
    print::optional_duration(out, activation_);
    out << ", high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", max_price_variation=";
    print::optional(out, max_price_variation_);
    out << ", unit_of_measure_qty=";
    print::optional(out, unit_of_measure_qty_);
    out << ", min_price_increment_amount=";
    print::optional(out, min_price_increment_amount_);
    out << ", price_ratio=";
    print::optional(out, price_ratio_);
    out << ", strike_price=";
    print::optional(out, strike_price_);
    out << ", raw_instrument_id=";
    out << raw_instrument_id_;
    out << ", leg_price=";
    print::optional(out, leg_price_);
    out << ", leg_delta=";
    print::optional(out, leg_delta_);
    out << ", inst_attrib_value=";
    out << inst_attrib_value_;
    out << ", underlying_id=";
    out << underlying_id_;
    out << ", market_depth_implied=";
    out << market_depth_implied_;
    out << ", market_depth=";
    out << market_depth_;
    out << ", market_segment_id=";
    out << market_segment_id_;
    out << ", max_trade_vol=";
    out << max_trade_vol_;
    out << ", min_lot_size=";
    out << min_lot_size_;
    out << ", min_lot_size_block=";
    out << min_lot_size_block_;
    out << ", min_lot_size_round_lot=";
    out << min_lot_size_round_lot_;
    out << ", min_trade_vol=";
    out << min_trade_vol_;
    out << ", contract_multiplier=";
    out << contract_multiplier_;
    out << ", decay_quantity=";
    out << decay_quantity_;
    out << ", original_contract_size=";
    out << original_contract_size_;
    out << ", leg_instrument_id=";
    out << leg_instrument_id_;
    out << ", leg_ratio_price_numerator=";
    out << leg_ratio_price_numerator_;
    out << ", leg_ratio_price_denominator=";
    out << leg_ratio_price_denominator_;
    out << ", leg_ratio_qty_numerator=";
    out << leg_ratio_qty_numerator_;
    out << ", leg_ratio_qty_denominator=";
    out << leg_ratio_qty_denominator_;
    out << ", leg_underlying_id=";
    out << leg_underlying_id_;
    out << ", appl_id=";
    out << appl_id_;
    out << ", maturity_year=";
    out << maturity_year_;
    out << ", decay_start_date=";
    out << decay_start_date_;
    out << ", channel=";
    out << channel_;
    out << ", leg_count=";
    out << leg_count_;
    out << ", leg_index=";
    out << leg_index_;
    out << ", currency=";
    print::text(out, currency_);
    out << ", settl_currency=";
    print::text(out, settl_currency_);
    out << ", secsubtype=";
    print::text(out, secsubtype_);
    out << ", raw_symbol=";
    print::text(out, raw_symbol_);
    out << ", group=";
    print::text(out, group_);
    out << ", exchange=";
    print::text(out, exchange_);
    out << ", asset=";
    print::text(out, asset_);
    out << ", cfi=";
    print::text(out, cfi_);
    out << ", security_type=";
    print::text(out, security_type_);
    out << ", unit_of_measure=";
    print::text(out, unit_of_measure_);
    out << ", underlying=";
    print::text(out, underlying_);
    out << ", strike_price_currency=";
    print::text(out, strike_price_currency_);
    out << ", leg_raw_symbol=";
    print::text(out, leg_raw_symbol_);
    out << ", instrument_class=";
    out << instrument_class_;
    out << ", match_algorithm=";
    out << match_algorithm_;
    out << ", main_fraction=";
    out << static_cast<int>(main_fraction_);
    out << ", price_display_format=";
    out << static_cast<int>(price_display_format_);
    out << ", sub_fraction=";
    out << static_cast<int>(sub_fraction_);
    out << ", underlying_product=";
    out << static_cast<int>(underlying_product_);
    out << ", security_update_action=";
    out << security_update_action_;
    out << ", maturity_month=";
    out << static_cast<int>(maturity_month_);
    out << ", maturity_day=";
    out << static_cast<int>(maturity_day_);
    out << ", maturity_week=";
    out << static_cast<int>(maturity_week_);
    out << ", user_defined_instrument=";
    out << user_defined_instrument_;
    out << ", contract_multiplier_unit=";
    out << static_cast<int>(contract_multiplier_unit_);
    out << ", flow_schedule_type=";
    out << static_cast<int>(flow_schedule_type_);
    out << ", tick_rule=";
    out << static_cast<int>(tick_rule_);
    out << ", leg_instrument_class=";
    out << leg_instrument_class_;
    out << ", leg_side=";
    out << leg_side_;
    out << ", reserved_17=";
    print::hex(out, reserved_17_.data(), reserved_17_.size());
    out << '}';
}

bool InstrumentDefMsg::equals(const Message& other) const {
    const auto* that = dynamic_cast<const InstrumentDefMsg*>(&other);
    return that != nullptr && *this == *that;
}

bool InstrumentDefMsg::operator==(const InstrumentDefMsg& other) const {
    return ts_recv_ == other.ts_recv_
        && min_price_increment_ == other.min_price_increment_
        && display_factor_ == other.display_factor_
        && expiration_ == other.expiration_
        && activation_ == other.activation_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && unit_of_measure_qty_ == other.unit_of_measure_qty_
        && min_price_increment_amount_ == other.min_price_increment_amount_
        && price_ratio_ == other.price_ratio_
        && strike_price_ == other.strike_price_
        && raw_instrument_id_ == other.raw_instrument_id_
        && leg_price_ == other.leg_price_
        && leg_delta_ == other.leg_delta_
        && inst_attrib_value_ == other.inst_attrib_value_
        && underlying_id_ == other.underlying_id_
        && market_depth_implied_ == other.market_depth_implied_
        && market_depth_ == other.market_depth_
        && market_segment_id_ == other.market_segment_id_
        && max_trade_vol_ == other.max_trade_vol_
        && min_lot_size_ == other.min_lot_size_
        && min_lot_size_block_ == other.min_lot_size_block_
        && min_lot_size_round_lot_ == other.min_lot_size_round_lot_
        && min_trade_vol_ == other.min_trade_vol_
        && contract_multiplier_ == other.contract_multiplier_
        && decay_quantity_ == other.decay_quantity_
        && original_contract_size_ == other.original_contract_size_
        && leg_instrument_id_ == other.leg_instrument_id_
        && leg_ratio_price_numerator_ == other.leg_ratio_price_numerator_
        && leg_ratio_price_denominator_ == other.leg_ratio_price_denominator_
        && leg_ratio_qty_numerator_ == other.leg_ratio_qty_numerator_
        && leg_ratio_qty_denominator_ == other.leg_ratio_qty_denominator_
        && leg_underlying_id_ == other.leg_underlying_id_
        && appl_id_ == other.appl_id_
        && maturity_year_ == other.maturity_year_
        && decay_start_date_ == other.decay_start_date_
        && channel_ == other.channel_
        && leg_count_ == other.leg_count_
        && leg_index_ == other.leg_index_
        && currency_ == other.currency_
        && settl_currency_ == other.settl_currency_
        && secsubtype_ == other.secsubtype_
        && raw_symbol_ == other.raw_symbol_
        && group_ == other.group_
        && exchange_ == other.exchange_
        && asset_ == other.asset_
        && cfi_ == other.cfi_
        && security_type_ == other.security_type_
        && unit_of_measure_ == other.unit_of_measure_
        && underlying_ == other.underlying_
        && strike_price_currency_ == other.strike_price_currency_
        && leg_raw_symbol_ == other.leg_raw_symbol_
        && instrument_class_ == other.instrument_class_
        && match_algorithm_ == other.match_algorithm_
        && main_fraction_ == other.main_fraction_
        && price_display_format_ == other.price_display_format_
        && sub_fraction_ == other.sub_fraction_
        && underlying_product_ == other.underlying_product_
        && security_update_action_ == other.security_update_action_
        && maturity_month_ == other.maturity_month_
        && maturity_day_ == other.maturity_day_
        && maturity_week_ == other.maturity_week_
        && user_defined_instrument_ == other.user_defined_instrument_
        && contract_multiplier_unit_ == other.contract_multiplier_unit_
        && flow_schedule_type_ == other.flow_schedule_type_
        && tick_rule_ == other.tick_rule_
        && leg_instrument_class_ == other.leg_instrument_class_
        && leg_side_ == other.leg_side_
        && reserved_17_ == other.reserved_17_;
}

bool InstrumentDefMsg::operator!=(const InstrumentDefMsg& other) const {
    return !(*this == other);
}

} // namespace databento::marketdata::normalized::dbn::v3
