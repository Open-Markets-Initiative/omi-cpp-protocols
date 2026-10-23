#include "MdInstrumentDefinitionFx.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

MdInstrumentDefinitionFx::MdInstrumentDefinitionFx(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const std::string& currency, const std::string& settl_currency, const std::string& price_quote_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, Decimal min_price_increment_ex, Decimal display_factor, std::uint8_t price_precision, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, char user_defined_instrument, const std::string& financial_instrument_full_name, const std::string& fx_currency_symbol, const std::string& settl_type, std::uint16_t intervening_days, const std::string& fx_benchmark_rate_fix, const std::string& rate_source, const std::string& fix_rate_local_time, const std::string& fix_rate_local_time_zone, std::uint32_t min_quote_life, Decimal max_price_discretion_offset, std::optional<std::uint64_t> instrument_guid, const MaturityMonthYear& maturity_month_year, const std::string& settlement_locale, std::optional<Decimal> alt_min_price_increment, std::optional<std::uint32_t> alt_min_quote_life, std::optional<Decimal> alt_price_increment_constraint, std::optional<Decimal> max_bid_ask_constraint, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const FxLotTypeRulesGroups& fx_lot_type_rules_groups, const TradingSessionsGroups& trading_sessions_groups)
  : match_event_indicator_(match_event_indicator), tot_num_reports_optional_(tot_num_reports_optional), security_update_action_(security_update_action), last_update_time_(last_update_time), md_security_trading_status_(md_security_trading_status), appl_id_(appl_id), market_segment_id_(market_segment_id), underlying_product_(underlying_product), security_exchange_(security_exchange), security_group_(security_group), asset_(asset), symbol_(symbol), security_id_(security_id), security_type_(security_type), cfi_code_(cfi_code), currency_(currency), settl_currency_(settl_currency), price_quote_currency_(price_quote_currency), match_algorithm_(match_algorithm), min_trade_vol_(min_trade_vol), max_trade_vol_(max_trade_vol), min_price_increment_ex_(min_price_increment_ex), display_factor_(display_factor), price_precision_(price_precision), unit_of_measure_(unit_of_measure), unit_of_measure_qty_(unit_of_measure_qty), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), user_defined_instrument_(user_defined_instrument), financial_instrument_full_name_(financial_instrument_full_name), fx_currency_symbol_(fx_currency_symbol), settl_type_(settl_type), intervening_days_(intervening_days), fx_benchmark_rate_fix_(fx_benchmark_rate_fix), rate_source_(rate_source), fix_rate_local_time_(fix_rate_local_time), fix_rate_local_time_zone_(fix_rate_local_time_zone), min_quote_life_(min_quote_life), max_price_discretion_offset_(max_price_discretion_offset), instrument_guid_(instrument_guid), maturity_month_year_(maturity_month_year), settlement_locale_(settlement_locale), alt_min_price_increment_(alt_min_price_increment), alt_min_quote_life_(alt_min_quote_life), alt_price_increment_constraint_(alt_price_increment_constraint), max_bid_ask_constraint_(max_bid_ask_constraint), events_groups_(events_groups), feed_types_groups_(feed_types_groups), inst_attrib_groups_(inst_attrib_groups), fx_lot_type_rules_groups_(fx_lot_type_rules_groups), trading_sessions_groups_(trading_sessions_groups) {}

const MatchEventIndicator& MdInstrumentDefinitionFx::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& MdInstrumentDefinitionFx::match_event_indicator() { return match_event_indicator_; }
void MdInstrumentDefinitionFx::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<std::uint32_t> MdInstrumentDefinitionFx::tot_num_reports_optional() const { return tot_num_reports_optional_; }
void MdInstrumentDefinitionFx::set_tot_num_reports_optional(std::optional<std::uint32_t> value) { tot_num_reports_optional_ = value; }

SecurityUpdateAction MdInstrumentDefinitionFx::security_update_action() const { return security_update_action_; }
void MdInstrumentDefinitionFx::set_security_update_action(SecurityUpdateAction value) { security_update_action_ = value; }

std::chrono::nanoseconds MdInstrumentDefinitionFx::last_update_time() const { return last_update_time_; }
void MdInstrumentDefinitionFx::set_last_update_time(std::chrono::nanoseconds value) { last_update_time_ = value; }

std::optional<MdSecurityTradingStatus> MdInstrumentDefinitionFx::md_security_trading_status() const { return md_security_trading_status_; }
void MdInstrumentDefinitionFx::set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value) { md_security_trading_status_ = value; }

std::int16_t MdInstrumentDefinitionFx::appl_id() const { return appl_id_; }
void MdInstrumentDefinitionFx::set_appl_id(std::int16_t value) { appl_id_ = value; }

std::uint8_t MdInstrumentDefinitionFx::market_segment_id() const { return market_segment_id_; }
void MdInstrumentDefinitionFx::set_market_segment_id(std::uint8_t value) { market_segment_id_ = value; }

std::uint8_t MdInstrumentDefinitionFx::underlying_product() const { return underlying_product_; }
void MdInstrumentDefinitionFx::set_underlying_product(std::uint8_t value) { underlying_product_ = value; }

const std::string& MdInstrumentDefinitionFx::security_exchange() const { return security_exchange_; }
std::string& MdInstrumentDefinitionFx::security_exchange() { return security_exchange_; }
void MdInstrumentDefinitionFx::set_security_exchange(const std::string& value) { security_exchange_ = value; }

const std::string& MdInstrumentDefinitionFx::security_group() const { return security_group_; }
std::string& MdInstrumentDefinitionFx::security_group() { return security_group_; }
void MdInstrumentDefinitionFx::set_security_group(const std::string& value) { security_group_ = value; }

const std::string& MdInstrumentDefinitionFx::asset() const { return asset_; }
std::string& MdInstrumentDefinitionFx::asset() { return asset_; }
void MdInstrumentDefinitionFx::set_asset(const std::string& value) { asset_ = value; }

const std::string& MdInstrumentDefinitionFx::symbol() const { return symbol_; }
std::string& MdInstrumentDefinitionFx::symbol() { return symbol_; }
void MdInstrumentDefinitionFx::set_symbol(const std::string& value) { symbol_ = value; }

std::int32_t MdInstrumentDefinitionFx::security_id() const { return security_id_; }
void MdInstrumentDefinitionFx::set_security_id(std::int32_t value) { security_id_ = value; }

const std::string& MdInstrumentDefinitionFx::security_type() const { return security_type_; }
std::string& MdInstrumentDefinitionFx::security_type() { return security_type_; }
void MdInstrumentDefinitionFx::set_security_type(const std::string& value) { security_type_ = value; }

const std::string& MdInstrumentDefinitionFx::cfi_code() const { return cfi_code_; }
std::string& MdInstrumentDefinitionFx::cfi_code() { return cfi_code_; }
void MdInstrumentDefinitionFx::set_cfi_code(const std::string& value) { cfi_code_ = value; }

const std::string& MdInstrumentDefinitionFx::currency() const { return currency_; }
std::string& MdInstrumentDefinitionFx::currency() { return currency_; }
void MdInstrumentDefinitionFx::set_currency(const std::string& value) { currency_ = value; }

const std::string& MdInstrumentDefinitionFx::settl_currency() const { return settl_currency_; }
std::string& MdInstrumentDefinitionFx::settl_currency() { return settl_currency_; }
void MdInstrumentDefinitionFx::set_settl_currency(const std::string& value) { settl_currency_ = value; }

const std::string& MdInstrumentDefinitionFx::price_quote_currency() const { return price_quote_currency_; }
std::string& MdInstrumentDefinitionFx::price_quote_currency() { return price_quote_currency_; }
void MdInstrumentDefinitionFx::set_price_quote_currency(const std::string& value) { price_quote_currency_ = value; }

char MdInstrumentDefinitionFx::match_algorithm() const { return match_algorithm_; }
void MdInstrumentDefinitionFx::set_match_algorithm(char value) { match_algorithm_ = value; }

std::uint32_t MdInstrumentDefinitionFx::min_trade_vol() const { return min_trade_vol_; }
void MdInstrumentDefinitionFx::set_min_trade_vol(std::uint32_t value) { min_trade_vol_ = value; }

std::uint32_t MdInstrumentDefinitionFx::max_trade_vol() const { return max_trade_vol_; }
void MdInstrumentDefinitionFx::set_max_trade_vol(std::uint32_t value) { max_trade_vol_ = value; }

Decimal MdInstrumentDefinitionFx::min_price_increment_ex() const { return min_price_increment_ex_; }
void MdInstrumentDefinitionFx::set_min_price_increment_ex(Decimal value) { min_price_increment_ex_ = value; }

Decimal MdInstrumentDefinitionFx::display_factor() const { return display_factor_; }
void MdInstrumentDefinitionFx::set_display_factor(Decimal value) { display_factor_ = value; }

std::uint8_t MdInstrumentDefinitionFx::price_precision() const { return price_precision_; }
void MdInstrumentDefinitionFx::set_price_precision(std::uint8_t value) { price_precision_ = value; }

const std::string& MdInstrumentDefinitionFx::unit_of_measure() const { return unit_of_measure_; }
std::string& MdInstrumentDefinitionFx::unit_of_measure() { return unit_of_measure_; }
void MdInstrumentDefinitionFx::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFx::unit_of_measure_qty() const { return unit_of_measure_qty_; }
void MdInstrumentDefinitionFx::set_unit_of_measure_qty(std::optional<Decimal> value) { unit_of_measure_qty_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFx::high_limit_price() const { return high_limit_price_; }
void MdInstrumentDefinitionFx::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFx::low_limit_price() const { return low_limit_price_; }
void MdInstrumentDefinitionFx::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFx::max_price_variation() const { return max_price_variation_; }
void MdInstrumentDefinitionFx::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

char MdInstrumentDefinitionFx::user_defined_instrument() const { return user_defined_instrument_; }
void MdInstrumentDefinitionFx::set_user_defined_instrument(char value) { user_defined_instrument_ = value; }

const std::string& MdInstrumentDefinitionFx::financial_instrument_full_name() const { return financial_instrument_full_name_; }
std::string& MdInstrumentDefinitionFx::financial_instrument_full_name() { return financial_instrument_full_name_; }
void MdInstrumentDefinitionFx::set_financial_instrument_full_name(const std::string& value) { financial_instrument_full_name_ = value; }

const std::string& MdInstrumentDefinitionFx::fx_currency_symbol() const { return fx_currency_symbol_; }
std::string& MdInstrumentDefinitionFx::fx_currency_symbol() { return fx_currency_symbol_; }
void MdInstrumentDefinitionFx::set_fx_currency_symbol(const std::string& value) { fx_currency_symbol_ = value; }

const std::string& MdInstrumentDefinitionFx::settl_type() const { return settl_type_; }
std::string& MdInstrumentDefinitionFx::settl_type() { return settl_type_; }
void MdInstrumentDefinitionFx::set_settl_type(const std::string& value) { settl_type_ = value; }

std::uint16_t MdInstrumentDefinitionFx::intervening_days() const { return intervening_days_; }
void MdInstrumentDefinitionFx::set_intervening_days(std::uint16_t value) { intervening_days_ = value; }

const std::string& MdInstrumentDefinitionFx::fx_benchmark_rate_fix() const { return fx_benchmark_rate_fix_; }
std::string& MdInstrumentDefinitionFx::fx_benchmark_rate_fix() { return fx_benchmark_rate_fix_; }
void MdInstrumentDefinitionFx::set_fx_benchmark_rate_fix(const std::string& value) { fx_benchmark_rate_fix_ = value; }

const std::string& MdInstrumentDefinitionFx::rate_source() const { return rate_source_; }
std::string& MdInstrumentDefinitionFx::rate_source() { return rate_source_; }
void MdInstrumentDefinitionFx::set_rate_source(const std::string& value) { rate_source_ = value; }

const std::string& MdInstrumentDefinitionFx::fix_rate_local_time() const { return fix_rate_local_time_; }
std::string& MdInstrumentDefinitionFx::fix_rate_local_time() { return fix_rate_local_time_; }
void MdInstrumentDefinitionFx::set_fix_rate_local_time(const std::string& value) { fix_rate_local_time_ = value; }

const std::string& MdInstrumentDefinitionFx::fix_rate_local_time_zone() const { return fix_rate_local_time_zone_; }
std::string& MdInstrumentDefinitionFx::fix_rate_local_time_zone() { return fix_rate_local_time_zone_; }
void MdInstrumentDefinitionFx::set_fix_rate_local_time_zone(const std::string& value) { fix_rate_local_time_zone_ = value; }

std::uint32_t MdInstrumentDefinitionFx::min_quote_life() const { return min_quote_life_; }
void MdInstrumentDefinitionFx::set_min_quote_life(std::uint32_t value) { min_quote_life_ = value; }

Decimal MdInstrumentDefinitionFx::max_price_discretion_offset() const { return max_price_discretion_offset_; }
void MdInstrumentDefinitionFx::set_max_price_discretion_offset(Decimal value) { max_price_discretion_offset_ = value; }

std::optional<std::uint64_t> MdInstrumentDefinitionFx::instrument_guid() const { return instrument_guid_; }
void MdInstrumentDefinitionFx::set_instrument_guid(std::optional<std::uint64_t> value) { instrument_guid_ = value; }

const MaturityMonthYear& MdInstrumentDefinitionFx::maturity_month_year() const { return maturity_month_year_; }
MaturityMonthYear& MdInstrumentDefinitionFx::maturity_month_year() { return maturity_month_year_; }
void MdInstrumentDefinitionFx::set_maturity_month_year(const MaturityMonthYear& value) { maturity_month_year_ = value; }

const std::string& MdInstrumentDefinitionFx::settlement_locale() const { return settlement_locale_; }
std::string& MdInstrumentDefinitionFx::settlement_locale() { return settlement_locale_; }
void MdInstrumentDefinitionFx::set_settlement_locale(const std::string& value) { settlement_locale_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFx::alt_min_price_increment() const { return alt_min_price_increment_; }
void MdInstrumentDefinitionFx::set_alt_min_price_increment(std::optional<Decimal> value) { alt_min_price_increment_ = value; }

std::optional<std::uint32_t> MdInstrumentDefinitionFx::alt_min_quote_life() const { return alt_min_quote_life_; }
void MdInstrumentDefinitionFx::set_alt_min_quote_life(std::optional<std::uint32_t> value) { alt_min_quote_life_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFx::alt_price_increment_constraint() const { return alt_price_increment_constraint_; }
void MdInstrumentDefinitionFx::set_alt_price_increment_constraint(std::optional<Decimal> value) { alt_price_increment_constraint_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFx::max_bid_ask_constraint() const { return max_bid_ask_constraint_; }
void MdInstrumentDefinitionFx::set_max_bid_ask_constraint(std::optional<Decimal> value) { max_bid_ask_constraint_ = value; }

const EventsGroups& MdInstrumentDefinitionFx::events_groups() const { return events_groups_; }
EventsGroups& MdInstrumentDefinitionFx::events_groups() { return events_groups_; }
void MdInstrumentDefinitionFx::set_events_groups(const EventsGroups& value) { events_groups_ = value; }

const FeedTypesGroups& MdInstrumentDefinitionFx::feed_types_groups() const { return feed_types_groups_; }
FeedTypesGroups& MdInstrumentDefinitionFx::feed_types_groups() { return feed_types_groups_; }
void MdInstrumentDefinitionFx::set_feed_types_groups(const FeedTypesGroups& value) { feed_types_groups_ = value; }

const InstAttribGroups& MdInstrumentDefinitionFx::inst_attrib_groups() const { return inst_attrib_groups_; }
InstAttribGroups& MdInstrumentDefinitionFx::inst_attrib_groups() { return inst_attrib_groups_; }
void MdInstrumentDefinitionFx::set_inst_attrib_groups(const InstAttribGroups& value) { inst_attrib_groups_ = value; }

const FxLotTypeRulesGroups& MdInstrumentDefinitionFx::fx_lot_type_rules_groups() const { return fx_lot_type_rules_groups_; }
FxLotTypeRulesGroups& MdInstrumentDefinitionFx::fx_lot_type_rules_groups() { return fx_lot_type_rules_groups_; }
void MdInstrumentDefinitionFx::set_fx_lot_type_rules_groups(const FxLotTypeRulesGroups& value) { fx_lot_type_rules_groups_ = value; }

const TradingSessionsGroups& MdInstrumentDefinitionFx::trading_sessions_groups() const { return trading_sessions_groups_; }
TradingSessionsGroups& MdInstrumentDefinitionFx::trading_sessions_groups() { return trading_sessions_groups_; }
void MdInstrumentDefinitionFx::set_trading_sessions_groups(const TradingSessionsGroups& value) { trading_sessions_groups_ = value; }

MktdataPayloadCode MdInstrumentDefinitionFx::type() const { return message_type; }

std::string_view MdInstrumentDefinitionFx::name() const { return "Md Instrument Definition Fx"; }

std::size_t MdInstrumentDefinitionFx::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("MdInstrumentDefinitionFx", offset + 4, length);
    tot_num_reports_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    wire::require("MdInstrumentDefinitionFx", offset + 1, length);
    security_update_action_ = static_cast<SecurityUpdateAction>(wire::read_char(data + offset));
    offset += 1;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    last_update_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 1, length);
    md_security_trading_status_ = wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("MdInstrumentDefinitionFx", offset + 2, length);
    appl_id_ = wire::read_i16_le(data + offset);
    offset += 2;

    wire::require("MdInstrumentDefinitionFx", offset + 1, length);
    market_segment_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFx", offset + 1, length);
    underlying_product_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFx", offset + 4, length);
    security_exchange_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    wire::require("MdInstrumentDefinitionFx", offset + 6, length);
    security_group_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFx", offset + 6, length);
    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFx", offset + 20, length);
    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("MdInstrumentDefinitionFx", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("MdInstrumentDefinitionFx", offset + 6, length);
    security_type_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFx", offset + 6, length);
    cfi_code_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFx", offset + 3, length);
    currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("MdInstrumentDefinitionFx", offset + 3, length);
    settl_currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("MdInstrumentDefinitionFx", offset + 3, length);
    price_quote_currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("MdInstrumentDefinitionFx", offset + 1, length);
    match_algorithm_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFx", offset + 4, length);
    min_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("MdInstrumentDefinitionFx", offset + 4, length);
    max_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    min_price_increment_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    display_factor_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 1, length);
    price_precision_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFx", offset + 30, length);
    unit_of_measure_ = wire::read_text(data + offset, 30, '\0');
    offset += 30;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    unit_of_measure_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 1, length);
    user_defined_instrument_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFx", offset + 35, length);
    financial_instrument_full_name_ = wire::read_text(data + offset, 35, '\0');
    offset += 35;

    wire::require("MdInstrumentDefinitionFx", offset + 7, length);
    fx_currency_symbol_ = wire::read_text(data + offset, 7, '\0');
    offset += 7;

    wire::require("MdInstrumentDefinitionFx", offset + 3, length);
    settl_type_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("MdInstrumentDefinitionFx", offset + 2, length);
    intervening_days_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("MdInstrumentDefinitionFx", offset + 20, length);
    fx_benchmark_rate_fix_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("MdInstrumentDefinitionFx", offset + 12, length);
    rate_source_ = wire::read_text(data + offset, 12, '\0');
    offset += 12;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    fix_rate_local_time_ = wire::read_text(data + offset, 8, '\0');
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 20, length);
    fix_rate_local_time_zone_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("MdInstrumentDefinitionFx", offset + 4, length);
    min_quote_life_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    max_price_discretion_offset_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    instrument_guid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    offset += maturity_month_year_.decode(data + offset, length - offset);

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    settlement_locale_ = wire::read_text(data + offset, 8, '\0');
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    alt_min_price_increment_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 4, length);
    alt_min_quote_life_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    alt_price_increment_constraint_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFx", offset + 8, length);
    max_bid_ask_constraint_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    offset += events_groups_.decode(data + offset, length - offset);

    offset += feed_types_groups_.decode(data + offset, length - offset);

    offset += inst_attrib_groups_.decode(data + offset, length - offset);

    offset += fx_lot_type_rules_groups_.decode(data + offset, length - offset);

    offset += trading_sessions_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t MdInstrumentDefinitionFx::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdInstrumentDefinitionFx", encoded_size(), capacity);

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

    wire::write_text(data + offset, 3, '\0', currency_);
    offset += 3;

    wire::write_text(data + offset, 3, '\0', settl_currency_);
    offset += 3;

    wire::write_text(data + offset, 3, '\0', price_quote_currency_);
    offset += 3;

    wire::write_char(data + offset, match_algorithm_);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(min_trade_vol_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(max_trade_vol_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(min_price_increment_ex_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(display_factor_.mantissa()));
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(price_precision_));
    offset += 1;

    wire::write_text(data + offset, 30, '\0', unit_of_measure_);
    offset += 30;

    wire::write_i64_le(data + offset, unit_of_measure_qty_ ? static_cast<std::int64_t>(unit_of_measure_qty_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ ? static_cast<std::int64_t>(max_price_variation_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_char(data + offset, user_defined_instrument_);
    offset += 1;

    wire::write_text(data + offset, 35, '\0', financial_instrument_full_name_);
    offset += 35;

    wire::write_text(data + offset, 7, '\0', fx_currency_symbol_);
    offset += 7;

    wire::write_text(data + offset, 3, '\0', settl_type_);
    offset += 3;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(intervening_days_));
    offset += 2;

    wire::write_text(data + offset, 20, '\0', fx_benchmark_rate_fix_);
    offset += 20;

    wire::write_text(data + offset, 12, '\0', rate_source_);
    offset += 12;

    wire::write_text(data + offset, 8, '\0', fix_rate_local_time_);
    offset += 8;

    wire::write_text(data + offset, 20, '\0', fix_rate_local_time_zone_);
    offset += 20;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(min_quote_life_));
    offset += 4;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(max_price_discretion_offset_.mantissa()));
    offset += 8;

    wire::write_u64_le(data + offset, instrument_guid_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    offset += maturity_month_year_.encode(data + offset, capacity - offset);

    wire::write_text(data + offset, 8, '\0', settlement_locale_);
    offset += 8;

    wire::write_i64_le(data + offset, alt_min_price_increment_ ? static_cast<std::int64_t>(alt_min_price_increment_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u32_le(data + offset, alt_min_quote_life_.value_or(static_cast<std::uint32_t>(4294967295ULL)));
    offset += 4;

    wire::write_i64_le(data + offset, alt_price_increment_constraint_ ? static_cast<std::int64_t>(alt_price_increment_constraint_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_bid_ask_constraint_ ? static_cast<std::int64_t>(max_bid_ask_constraint_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    offset += events_groups_.encode(data + offset, capacity - offset);

    offset += feed_types_groups_.encode(data + offset, capacity - offset);

    offset += inst_attrib_groups_.encode(data + offset, capacity - offset);

    offset += fx_lot_type_rules_groups_.encode(data + offset, capacity - offset);

    offset += trading_sessions_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MdInstrumentDefinitionFx::encoded_size() const {
    return match_event_indicator_.encoded_size() + 4 + 1 + 8 + 1 + 2 + 1 + 1 + 4 + 6 + 6 + 20 + 4 + 6 + 6 + 3 + 3 + 3 + 1 + 4 + 4 + 8 + 8 + 1 + 30 + 8 + 8 + 8 + 8 + 1 + 35 + 7 + 3 + 2 + 20 + 12 + 8 + 20 + 4 + 8 + 8 + maturity_month_year_.encoded_size() + 8 + 8 + 4 + 8 + 8 + events_groups_.encoded_size() + feed_types_groups_.encoded_size() + inst_attrib_groups_.encoded_size() + fx_lot_type_rules_groups_.encoded_size() + trading_sessions_groups_.encoded_size();
}

void MdInstrumentDefinitionFx::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> MdInstrumentDefinitionFx::clone() const {
    return std::make_unique<MdInstrumentDefinitionFx>(*this);
}

void MdInstrumentDefinitionFx::print(std::ostream& out) const {
    out << "MdInstrumentDefinitionFx{";
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
    out << ", currency=";
    print::text(out, currency_);
    out << ", settl_currency=";
    print::text(out, settl_currency_);
    out << ", price_quote_currency=";
    print::text(out, price_quote_currency_);
    out << ", match_algorithm=";
    print::character(out, match_algorithm_);
    out << ", min_trade_vol=";
    out << min_trade_vol_;
    out << ", max_trade_vol=";
    out << max_trade_vol_;
    out << ", min_price_increment_ex=";
    out << min_price_increment_ex_;
    out << ", display_factor=";
    out << display_factor_;
    out << ", price_precision=";
    out << static_cast<int>(price_precision_);
    out << ", unit_of_measure=";
    print::text(out, unit_of_measure_);
    out << ", unit_of_measure_qty=";
    print::optional(out, unit_of_measure_qty_);
    out << ", high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", max_price_variation=";
    print::optional(out, max_price_variation_);
    out << ", user_defined_instrument=";
    print::character(out, user_defined_instrument_);
    out << ", financial_instrument_full_name=";
    print::text(out, financial_instrument_full_name_);
    out << ", fx_currency_symbol=";
    print::text(out, fx_currency_symbol_);
    out << ", settl_type=";
    print::text(out, settl_type_);
    out << ", intervening_days=";
    out << intervening_days_;
    out << ", fx_benchmark_rate_fix=";
    print::text(out, fx_benchmark_rate_fix_);
    out << ", rate_source=";
    print::text(out, rate_source_);
    out << ", fix_rate_local_time=";
    print::text(out, fix_rate_local_time_);
    out << ", fix_rate_local_time_zone=";
    print::text(out, fix_rate_local_time_zone_);
    out << ", min_quote_life=";
    out << min_quote_life_;
    out << ", max_price_discretion_offset=";
    out << max_price_discretion_offset_;
    out << ", instrument_guid=";
    print::optional(out, instrument_guid_);
    out << ", maturity_month_year=";
    maturity_month_year_.print(out);
    out << ", settlement_locale=";
    print::text(out, settlement_locale_);
    out << ", alt_min_price_increment=";
    print::optional(out, alt_min_price_increment_);
    out << ", alt_min_quote_life=";
    print::optional(out, alt_min_quote_life_);
    out << ", alt_price_increment_constraint=";
    print::optional(out, alt_price_increment_constraint_);
    out << ", max_bid_ask_constraint=";
    print::optional(out, max_bid_ask_constraint_);
    out << ", events_groups=";
    events_groups_.print(out);
    out << ", feed_types_groups=";
    feed_types_groups_.print(out);
    out << ", inst_attrib_groups=";
    inst_attrib_groups_.print(out);
    out << ", fx_lot_type_rules_groups=";
    fx_lot_type_rules_groups_.print(out);
    out << ", trading_sessions_groups=";
    trading_sessions_groups_.print(out);
    out << '}';
}

bool MdInstrumentDefinitionFx::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const MdInstrumentDefinitionFx*>(&other);
    return that != nullptr && *this == *that;
}

bool MdInstrumentDefinitionFx::operator==(const MdInstrumentDefinitionFx& other) const {
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
        && currency_ == other.currency_
        && settl_currency_ == other.settl_currency_
        && price_quote_currency_ == other.price_quote_currency_
        && match_algorithm_ == other.match_algorithm_
        && min_trade_vol_ == other.min_trade_vol_
        && max_trade_vol_ == other.max_trade_vol_
        && min_price_increment_ex_ == other.min_price_increment_ex_
        && display_factor_ == other.display_factor_
        && price_precision_ == other.price_precision_
        && unit_of_measure_ == other.unit_of_measure_
        && unit_of_measure_qty_ == other.unit_of_measure_qty_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && user_defined_instrument_ == other.user_defined_instrument_
        && financial_instrument_full_name_ == other.financial_instrument_full_name_
        && fx_currency_symbol_ == other.fx_currency_symbol_
        && settl_type_ == other.settl_type_
        && intervening_days_ == other.intervening_days_
        && fx_benchmark_rate_fix_ == other.fx_benchmark_rate_fix_
        && rate_source_ == other.rate_source_
        && fix_rate_local_time_ == other.fix_rate_local_time_
        && fix_rate_local_time_zone_ == other.fix_rate_local_time_zone_
        && min_quote_life_ == other.min_quote_life_
        && max_price_discretion_offset_ == other.max_price_discretion_offset_
        && instrument_guid_ == other.instrument_guid_
        && maturity_month_year_ == other.maturity_month_year_
        && settlement_locale_ == other.settlement_locale_
        && alt_min_price_increment_ == other.alt_min_price_increment_
        && alt_min_quote_life_ == other.alt_min_quote_life_
        && alt_price_increment_constraint_ == other.alt_price_increment_constraint_
        && max_bid_ask_constraint_ == other.max_bid_ask_constraint_
        && events_groups_ == other.events_groups_
        && feed_types_groups_ == other.feed_types_groups_
        && inst_attrib_groups_ == other.inst_attrib_groups_
        && fx_lot_type_rules_groups_ == other.fx_lot_type_rules_groups_
        && trading_sessions_groups_ == other.trading_sessions_groups_;
}

bool MdInstrumentDefinitionFx::operator!=(const MdInstrumentDefinitionFx& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
