#include "MdInstrumentDefinitionFixedIncome.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

MdInstrumentDefinitionFixedIncome::MdInstrumentDefinitionFixedIncome(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const std::string& currency, const std::string& settl_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, std::optional<Decimal> min_price_increment_optional_ex, Decimal display_factor, std::optional<std::uint8_t> main_fraction, std::optional<std::uint8_t> sub_fraction, std::optional<std::uint8_t> price_display_format, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> trading_reference_price, std::optional<std::uint16_t> trading_reference_date, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::optional<Decimal> min_price_increment_amount, std::optional<std::uint16_t> issue_date, std::optional<std::uint16_t> dated_date, std::optional<std::uint16_t> maturity_date, std::optional<Decimal> coupon_rate, std::optional<Decimal> par_value, const std::string& coupon_frequency_unit, std::optional<std::uint16_t> coupon_frequency_period, const std::string& coupon_day_count, const std::string& country_of_issue, const std::string& issuer, const std::string& financial_instrument_full_name, const std::string& security_alt_id, std::optional<SecurityAltIdSource> security_alt_id_source, const std::string& price_quote_method, const std::string& party_role_clearing_org, char user_defined_instrument, const std::string& risk_set, const std::string& market_set, std::optional<std::uint64_t> instrument_guid, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups)
  : match_event_indicator_(match_event_indicator), tot_num_reports_optional_(tot_num_reports_optional), security_update_action_(security_update_action), last_update_time_(last_update_time), md_security_trading_status_(md_security_trading_status), appl_id_(appl_id), market_segment_id_(market_segment_id), underlying_product_(underlying_product), security_exchange_(security_exchange), security_group_(security_group), asset_(asset), symbol_(symbol), security_id_(security_id), security_type_(security_type), cfi_code_(cfi_code), currency_(currency), settl_currency_(settl_currency), match_algorithm_(match_algorithm), min_trade_vol_(min_trade_vol), max_trade_vol_(max_trade_vol), min_price_increment_optional_ex_(min_price_increment_optional_ex), display_factor_(display_factor), main_fraction_(main_fraction), sub_fraction_(sub_fraction), price_display_format_(price_display_format), unit_of_measure_(unit_of_measure), unit_of_measure_qty_(unit_of_measure_qty), trading_reference_price_(trading_reference_price), trading_reference_date_(trading_reference_date), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), min_price_increment_amount_(min_price_increment_amount), issue_date_(issue_date), dated_date_(dated_date), maturity_date_(maturity_date), coupon_rate_(coupon_rate), par_value_(par_value), coupon_frequency_unit_(coupon_frequency_unit), coupon_frequency_period_(coupon_frequency_period), coupon_day_count_(coupon_day_count), country_of_issue_(country_of_issue), issuer_(issuer), financial_instrument_full_name_(financial_instrument_full_name), security_alt_id_(security_alt_id), security_alt_id_source_(security_alt_id_source), price_quote_method_(price_quote_method), party_role_clearing_org_(party_role_clearing_org), user_defined_instrument_(user_defined_instrument), risk_set_(risk_set), market_set_(market_set), instrument_guid_(instrument_guid), events_groups_(events_groups), feed_types_groups_(feed_types_groups), inst_attrib_groups_(inst_attrib_groups), lot_type_rules_groups_(lot_type_rules_groups) {}

const MatchEventIndicator& MdInstrumentDefinitionFixedIncome::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& MdInstrumentDefinitionFixedIncome::match_event_indicator() { return match_event_indicator_; }
void MdInstrumentDefinitionFixedIncome::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<std::uint32_t> MdInstrumentDefinitionFixedIncome::tot_num_reports_optional() const { return tot_num_reports_optional_; }
void MdInstrumentDefinitionFixedIncome::set_tot_num_reports_optional(std::optional<std::uint32_t> value) { tot_num_reports_optional_ = value; }

SecurityUpdateAction MdInstrumentDefinitionFixedIncome::security_update_action() const { return security_update_action_; }
void MdInstrumentDefinitionFixedIncome::set_security_update_action(SecurityUpdateAction value) { security_update_action_ = value; }

std::chrono::nanoseconds MdInstrumentDefinitionFixedIncome::last_update_time() const { return last_update_time_; }
void MdInstrumentDefinitionFixedIncome::set_last_update_time(std::chrono::nanoseconds value) { last_update_time_ = value; }

std::optional<MdSecurityTradingStatus> MdInstrumentDefinitionFixedIncome::md_security_trading_status() const { return md_security_trading_status_; }
void MdInstrumentDefinitionFixedIncome::set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value) { md_security_trading_status_ = value; }

std::int16_t MdInstrumentDefinitionFixedIncome::appl_id() const { return appl_id_; }
void MdInstrumentDefinitionFixedIncome::set_appl_id(std::int16_t value) { appl_id_ = value; }

std::uint8_t MdInstrumentDefinitionFixedIncome::market_segment_id() const { return market_segment_id_; }
void MdInstrumentDefinitionFixedIncome::set_market_segment_id(std::uint8_t value) { market_segment_id_ = value; }

std::uint8_t MdInstrumentDefinitionFixedIncome::underlying_product() const { return underlying_product_; }
void MdInstrumentDefinitionFixedIncome::set_underlying_product(std::uint8_t value) { underlying_product_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::security_exchange() const { return security_exchange_; }
std::string& MdInstrumentDefinitionFixedIncome::security_exchange() { return security_exchange_; }
void MdInstrumentDefinitionFixedIncome::set_security_exchange(const std::string& value) { security_exchange_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::security_group() const { return security_group_; }
std::string& MdInstrumentDefinitionFixedIncome::security_group() { return security_group_; }
void MdInstrumentDefinitionFixedIncome::set_security_group(const std::string& value) { security_group_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::asset() const { return asset_; }
std::string& MdInstrumentDefinitionFixedIncome::asset() { return asset_; }
void MdInstrumentDefinitionFixedIncome::set_asset(const std::string& value) { asset_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::symbol() const { return symbol_; }
std::string& MdInstrumentDefinitionFixedIncome::symbol() { return symbol_; }
void MdInstrumentDefinitionFixedIncome::set_symbol(const std::string& value) { symbol_ = value; }

std::int32_t MdInstrumentDefinitionFixedIncome::security_id() const { return security_id_; }
void MdInstrumentDefinitionFixedIncome::set_security_id(std::int32_t value) { security_id_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::security_type() const { return security_type_; }
std::string& MdInstrumentDefinitionFixedIncome::security_type() { return security_type_; }
void MdInstrumentDefinitionFixedIncome::set_security_type(const std::string& value) { security_type_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::cfi_code() const { return cfi_code_; }
std::string& MdInstrumentDefinitionFixedIncome::cfi_code() { return cfi_code_; }
void MdInstrumentDefinitionFixedIncome::set_cfi_code(const std::string& value) { cfi_code_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::currency() const { return currency_; }
std::string& MdInstrumentDefinitionFixedIncome::currency() { return currency_; }
void MdInstrumentDefinitionFixedIncome::set_currency(const std::string& value) { currency_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::settl_currency() const { return settl_currency_; }
std::string& MdInstrumentDefinitionFixedIncome::settl_currency() { return settl_currency_; }
void MdInstrumentDefinitionFixedIncome::set_settl_currency(const std::string& value) { settl_currency_ = value; }

char MdInstrumentDefinitionFixedIncome::match_algorithm() const { return match_algorithm_; }
void MdInstrumentDefinitionFixedIncome::set_match_algorithm(char value) { match_algorithm_ = value; }

std::uint32_t MdInstrumentDefinitionFixedIncome::min_trade_vol() const { return min_trade_vol_; }
void MdInstrumentDefinitionFixedIncome::set_min_trade_vol(std::uint32_t value) { min_trade_vol_ = value; }

std::uint32_t MdInstrumentDefinitionFixedIncome::max_trade_vol() const { return max_trade_vol_; }
void MdInstrumentDefinitionFixedIncome::set_max_trade_vol(std::uint32_t value) { max_trade_vol_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::min_price_increment_optional_ex() const { return min_price_increment_optional_ex_; }
void MdInstrumentDefinitionFixedIncome::set_min_price_increment_optional_ex(std::optional<Decimal> value) { min_price_increment_optional_ex_ = value; }

Decimal MdInstrumentDefinitionFixedIncome::display_factor() const { return display_factor_; }
void MdInstrumentDefinitionFixedIncome::set_display_factor(Decimal value) { display_factor_ = value; }

std::optional<std::uint8_t> MdInstrumentDefinitionFixedIncome::main_fraction() const { return main_fraction_; }
void MdInstrumentDefinitionFixedIncome::set_main_fraction(std::optional<std::uint8_t> value) { main_fraction_ = value; }

std::optional<std::uint8_t> MdInstrumentDefinitionFixedIncome::sub_fraction() const { return sub_fraction_; }
void MdInstrumentDefinitionFixedIncome::set_sub_fraction(std::optional<std::uint8_t> value) { sub_fraction_ = value; }

std::optional<std::uint8_t> MdInstrumentDefinitionFixedIncome::price_display_format() const { return price_display_format_; }
void MdInstrumentDefinitionFixedIncome::set_price_display_format(std::optional<std::uint8_t> value) { price_display_format_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::unit_of_measure() const { return unit_of_measure_; }
std::string& MdInstrumentDefinitionFixedIncome::unit_of_measure() { return unit_of_measure_; }
void MdInstrumentDefinitionFixedIncome::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::unit_of_measure_qty() const { return unit_of_measure_qty_; }
void MdInstrumentDefinitionFixedIncome::set_unit_of_measure_qty(std::optional<Decimal> value) { unit_of_measure_qty_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::trading_reference_price() const { return trading_reference_price_; }
void MdInstrumentDefinitionFixedIncome::set_trading_reference_price(std::optional<Decimal> value) { trading_reference_price_ = value; }

std::optional<std::uint16_t> MdInstrumentDefinitionFixedIncome::trading_reference_date() const { return trading_reference_date_; }
void MdInstrumentDefinitionFixedIncome::set_trading_reference_date(std::optional<std::uint16_t> value) { trading_reference_date_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::high_limit_price() const { return high_limit_price_; }
void MdInstrumentDefinitionFixedIncome::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::low_limit_price() const { return low_limit_price_; }
void MdInstrumentDefinitionFixedIncome::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::max_price_variation() const { return max_price_variation_; }
void MdInstrumentDefinitionFixedIncome::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::min_price_increment_amount() const { return min_price_increment_amount_; }
void MdInstrumentDefinitionFixedIncome::set_min_price_increment_amount(std::optional<Decimal> value) { min_price_increment_amount_ = value; }

std::optional<std::uint16_t> MdInstrumentDefinitionFixedIncome::issue_date() const { return issue_date_; }
void MdInstrumentDefinitionFixedIncome::set_issue_date(std::optional<std::uint16_t> value) { issue_date_ = value; }

std::optional<std::uint16_t> MdInstrumentDefinitionFixedIncome::dated_date() const { return dated_date_; }
void MdInstrumentDefinitionFixedIncome::set_dated_date(std::optional<std::uint16_t> value) { dated_date_ = value; }

std::optional<std::uint16_t> MdInstrumentDefinitionFixedIncome::maturity_date() const { return maturity_date_; }
void MdInstrumentDefinitionFixedIncome::set_maturity_date(std::optional<std::uint16_t> value) { maturity_date_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::coupon_rate() const { return coupon_rate_; }
void MdInstrumentDefinitionFixedIncome::set_coupon_rate(std::optional<Decimal> value) { coupon_rate_ = value; }

std::optional<Decimal> MdInstrumentDefinitionFixedIncome::par_value() const { return par_value_; }
void MdInstrumentDefinitionFixedIncome::set_par_value(std::optional<Decimal> value) { par_value_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::coupon_frequency_unit() const { return coupon_frequency_unit_; }
std::string& MdInstrumentDefinitionFixedIncome::coupon_frequency_unit() { return coupon_frequency_unit_; }
void MdInstrumentDefinitionFixedIncome::set_coupon_frequency_unit(const std::string& value) { coupon_frequency_unit_ = value; }

std::optional<std::uint16_t> MdInstrumentDefinitionFixedIncome::coupon_frequency_period() const { return coupon_frequency_period_; }
void MdInstrumentDefinitionFixedIncome::set_coupon_frequency_period(std::optional<std::uint16_t> value) { coupon_frequency_period_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::coupon_day_count() const { return coupon_day_count_; }
std::string& MdInstrumentDefinitionFixedIncome::coupon_day_count() { return coupon_day_count_; }
void MdInstrumentDefinitionFixedIncome::set_coupon_day_count(const std::string& value) { coupon_day_count_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::country_of_issue() const { return country_of_issue_; }
std::string& MdInstrumentDefinitionFixedIncome::country_of_issue() { return country_of_issue_; }
void MdInstrumentDefinitionFixedIncome::set_country_of_issue(const std::string& value) { country_of_issue_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::issuer() const { return issuer_; }
std::string& MdInstrumentDefinitionFixedIncome::issuer() { return issuer_; }
void MdInstrumentDefinitionFixedIncome::set_issuer(const std::string& value) { issuer_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::financial_instrument_full_name() const { return financial_instrument_full_name_; }
std::string& MdInstrumentDefinitionFixedIncome::financial_instrument_full_name() { return financial_instrument_full_name_; }
void MdInstrumentDefinitionFixedIncome::set_financial_instrument_full_name(const std::string& value) { financial_instrument_full_name_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::security_alt_id() const { return security_alt_id_; }
std::string& MdInstrumentDefinitionFixedIncome::security_alt_id() { return security_alt_id_; }
void MdInstrumentDefinitionFixedIncome::set_security_alt_id(const std::string& value) { security_alt_id_ = value; }

std::optional<SecurityAltIdSource> MdInstrumentDefinitionFixedIncome::security_alt_id_source() const { return security_alt_id_source_; }
void MdInstrumentDefinitionFixedIncome::set_security_alt_id_source(std::optional<SecurityAltIdSource> value) { security_alt_id_source_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::price_quote_method() const { return price_quote_method_; }
std::string& MdInstrumentDefinitionFixedIncome::price_quote_method() { return price_quote_method_; }
void MdInstrumentDefinitionFixedIncome::set_price_quote_method(const std::string& value) { price_quote_method_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::party_role_clearing_org() const { return party_role_clearing_org_; }
std::string& MdInstrumentDefinitionFixedIncome::party_role_clearing_org() { return party_role_clearing_org_; }
void MdInstrumentDefinitionFixedIncome::set_party_role_clearing_org(const std::string& value) { party_role_clearing_org_ = value; }

char MdInstrumentDefinitionFixedIncome::user_defined_instrument() const { return user_defined_instrument_; }
void MdInstrumentDefinitionFixedIncome::set_user_defined_instrument(char value) { user_defined_instrument_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::risk_set() const { return risk_set_; }
std::string& MdInstrumentDefinitionFixedIncome::risk_set() { return risk_set_; }
void MdInstrumentDefinitionFixedIncome::set_risk_set(const std::string& value) { risk_set_ = value; }

const std::string& MdInstrumentDefinitionFixedIncome::market_set() const { return market_set_; }
std::string& MdInstrumentDefinitionFixedIncome::market_set() { return market_set_; }
void MdInstrumentDefinitionFixedIncome::set_market_set(const std::string& value) { market_set_ = value; }

std::optional<std::uint64_t> MdInstrumentDefinitionFixedIncome::instrument_guid() const { return instrument_guid_; }
void MdInstrumentDefinitionFixedIncome::set_instrument_guid(std::optional<std::uint64_t> value) { instrument_guid_ = value; }

const EventsGroups& MdInstrumentDefinitionFixedIncome::events_groups() const { return events_groups_; }
EventsGroups& MdInstrumentDefinitionFixedIncome::events_groups() { return events_groups_; }
void MdInstrumentDefinitionFixedIncome::set_events_groups(const EventsGroups& value) { events_groups_ = value; }

const FeedTypesGroups& MdInstrumentDefinitionFixedIncome::feed_types_groups() const { return feed_types_groups_; }
FeedTypesGroups& MdInstrumentDefinitionFixedIncome::feed_types_groups() { return feed_types_groups_; }
void MdInstrumentDefinitionFixedIncome::set_feed_types_groups(const FeedTypesGroups& value) { feed_types_groups_ = value; }

const InstAttribGroups& MdInstrumentDefinitionFixedIncome::inst_attrib_groups() const { return inst_attrib_groups_; }
InstAttribGroups& MdInstrumentDefinitionFixedIncome::inst_attrib_groups() { return inst_attrib_groups_; }
void MdInstrumentDefinitionFixedIncome::set_inst_attrib_groups(const InstAttribGroups& value) { inst_attrib_groups_ = value; }

const LotTypeRulesGroups& MdInstrumentDefinitionFixedIncome::lot_type_rules_groups() const { return lot_type_rules_groups_; }
LotTypeRulesGroups& MdInstrumentDefinitionFixedIncome::lot_type_rules_groups() { return lot_type_rules_groups_; }
void MdInstrumentDefinitionFixedIncome::set_lot_type_rules_groups(const LotTypeRulesGroups& value) { lot_type_rules_groups_ = value; }

MktdataPayloadCode MdInstrumentDefinitionFixedIncome::type() const { return message_type; }

std::string_view MdInstrumentDefinitionFixedIncome::name() const { return "Md Instrument Definition Fixed Income"; }

std::size_t MdInstrumentDefinitionFixedIncome::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 4, length);
    tot_num_reports_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    security_update_action_ = static_cast<SecurityUpdateAction>(wire::read_char(data + offset));
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    last_update_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    md_security_trading_status_ = wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 2, length);
    appl_id_ = wire::read_i16_le(data + offset);
    offset += 2;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    market_segment_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    underlying_product_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 4, length);
    security_exchange_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 6, length);
    security_group_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 6, length);
    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 20, length);
    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 6, length);
    security_type_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 6, length);
    cfi_code_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 3, length);
    currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 3, length);
    settl_currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    match_algorithm_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 4, length);
    min_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 4, length);
    max_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    min_price_increment_optional_ex_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    display_factor_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    main_fraction_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    sub_fraction_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    price_display_format_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 30, length);
    unit_of_measure_ = wire::read_text(data + offset, 30, '\0');
    offset += 30;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    unit_of_measure_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    trading_reference_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 2, length);
    trading_reference_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    min_price_increment_amount_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 2, length);
    issue_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 2, length);
    dated_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 2, length);
    maturity_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    coupon_rate_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    par_value_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 3, length);
    coupon_frequency_unit_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 2, length);
    coupon_frequency_period_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 20, length);
    coupon_day_count_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 2, length);
    country_of_issue_ = wire::read_text(data + offset, 2, '\0');
    offset += 2;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 25, length);
    issuer_ = wire::read_text(data + offset, 25, '\0');
    offset += 25;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 35, length);
    financial_instrument_full_name_ = wire::read_text(data + offset, 35, '\0');
    offset += 35;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 12, length);
    security_alt_id_ = wire::read_text(data + offset, 12, '\0');
    offset += 12;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    security_alt_id_source_ = wire::nullable_enum<SecurityAltIdSource>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 5, length);
    price_quote_method_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 5, length);
    party_role_clearing_org_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 1, length);
    user_defined_instrument_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 6, length);
    risk_set_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 6, length);
    market_set_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("MdInstrumentDefinitionFixedIncome", offset + 8, length);
    instrument_guid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    offset += events_groups_.decode(data + offset, length - offset);

    offset += feed_types_groups_.decode(data + offset, length - offset);

    offset += inst_attrib_groups_.decode(data + offset, length - offset);

    offset += lot_type_rules_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t MdInstrumentDefinitionFixedIncome::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("MdInstrumentDefinitionFixedIncome", encoded_size(), capacity);

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

    wire::write_char(data + offset, match_algorithm_);
    offset += 1;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(min_trade_vol_));
    offset += 4;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(max_trade_vol_));
    offset += 4;

    wire::write_i64_le(data + offset, min_price_increment_optional_ex_ ? static_cast<std::int64_t>(min_price_increment_optional_ex_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
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

    wire::write_u16_le(data + offset, trading_reference_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_i64_le(data + offset, high_limit_price_ ? static_cast<std::int64_t>(high_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, low_limit_price_ ? static_cast<std::int64_t>(low_limit_price_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, max_price_variation_ ? static_cast<std::int64_t>(max_price_variation_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, min_price_increment_amount_ ? static_cast<std::int64_t>(min_price_increment_amount_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_u16_le(data + offset, issue_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u16_le(data + offset, dated_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u16_le(data + offset, maturity_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_i64_le(data + offset, coupon_rate_ ? static_cast<std::int64_t>(coupon_rate_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_i64_le(data + offset, par_value_ ? static_cast<std::int64_t>(par_value_->mantissa()) : static_cast<std::int64_t>(9223372036854775807LL));
    offset += 8;

    wire::write_text(data + offset, 3, '\0', coupon_frequency_unit_);
    offset += 3;

    wire::write_u16_le(data + offset, coupon_frequency_period_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_text(data + offset, 20, '\0', coupon_day_count_);
    offset += 20;

    wire::write_text(data + offset, 2, '\0', country_of_issue_);
    offset += 2;

    wire::write_text(data + offset, 25, '\0', issuer_);
    offset += 25;

    wire::write_text(data + offset, 35, '\0', financial_instrument_full_name_);
    offset += 35;

    wire::write_text(data + offset, 12, '\0', security_alt_id_);
    offset += 12;

    wire::write_u8(data + offset, security_alt_id_source_ ? static_cast<std::uint8_t>(*security_alt_id_source_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_text(data + offset, 5, '\0', price_quote_method_);
    offset += 5;

    wire::write_text(data + offset, 5, '\0', party_role_clearing_org_);
    offset += 5;

    wire::write_char(data + offset, user_defined_instrument_);
    offset += 1;

    wire::write_text(data + offset, 6, '\0', risk_set_);
    offset += 6;

    wire::write_text(data + offset, 6, '\0', market_set_);
    offset += 6;

    wire::write_u64_le(data + offset, instrument_guid_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    offset += events_groups_.encode(data + offset, capacity - offset);

    offset += feed_types_groups_.encode(data + offset, capacity - offset);

    offset += inst_attrib_groups_.encode(data + offset, capacity - offset);

    offset += lot_type_rules_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t MdInstrumentDefinitionFixedIncome::encoded_size() const {
    return match_event_indicator_.encoded_size() + 4 + 1 + 8 + 1 + 2 + 1 + 1 + 4 + 6 + 6 + 20 + 4 + 6 + 6 + 3 + 3 + 1 + 4 + 4 + 8 + 8 + 1 + 1 + 1 + 30 + 8 + 8 + 2 + 8 + 8 + 8 + 8 + 2 + 2 + 2 + 8 + 8 + 3 + 2 + 20 + 2 + 25 + 35 + 12 + 1 + 5 + 5 + 1 + 6 + 6 + 8 + events_groups_.encoded_size() + feed_types_groups_.encoded_size() + inst_attrib_groups_.encoded_size() + lot_type_rules_groups_.encoded_size();
}

void MdInstrumentDefinitionFixedIncome::accept(MktdataPayloadVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<MktdataPayload> MdInstrumentDefinitionFixedIncome::clone() const {
    return std::make_unique<MdInstrumentDefinitionFixedIncome>(*this);
}

void MdInstrumentDefinitionFixedIncome::print(std::ostream& out) const {
    out << "MdInstrumentDefinitionFixedIncome{";
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
    out << ", match_algorithm=";
    print::character(out, match_algorithm_);
    out << ", min_trade_vol=";
    out << min_trade_vol_;
    out << ", max_trade_vol=";
    out << max_trade_vol_;
    out << ", min_price_increment_optional_ex=";
    print::optional(out, min_price_increment_optional_ex_);
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
    out << ", trading_reference_date=";
    print::optional(out, trading_reference_date_);
    out << ", high_limit_price=";
    print::optional(out, high_limit_price_);
    out << ", low_limit_price=";
    print::optional(out, low_limit_price_);
    out << ", max_price_variation=";
    print::optional(out, max_price_variation_);
    out << ", min_price_increment_amount=";
    print::optional(out, min_price_increment_amount_);
    out << ", issue_date=";
    print::optional(out, issue_date_);
    out << ", dated_date=";
    print::optional(out, dated_date_);
    out << ", maturity_date=";
    print::optional(out, maturity_date_);
    out << ", coupon_rate=";
    print::optional(out, coupon_rate_);
    out << ", par_value=";
    print::optional(out, par_value_);
    out << ", coupon_frequency_unit=";
    print::text(out, coupon_frequency_unit_);
    out << ", coupon_frequency_period=";
    print::optional(out, coupon_frequency_period_);
    out << ", coupon_day_count=";
    print::text(out, coupon_day_count_);
    out << ", country_of_issue=";
    print::text(out, country_of_issue_);
    out << ", issuer=";
    print::text(out, issuer_);
    out << ", financial_instrument_full_name=";
    print::text(out, financial_instrument_full_name_);
    out << ", security_alt_id=";
    print::text(out, security_alt_id_);
    out << ", security_alt_id_source=";
    print::optional(out, security_alt_id_source_);
    out << ", price_quote_method=";
    print::text(out, price_quote_method_);
    out << ", party_role_clearing_org=";
    print::text(out, party_role_clearing_org_);
    out << ", user_defined_instrument=";
    print::character(out, user_defined_instrument_);
    out << ", risk_set=";
    print::text(out, risk_set_);
    out << ", market_set=";
    print::text(out, market_set_);
    out << ", instrument_guid=";
    print::optional(out, instrument_guid_);
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

bool MdInstrumentDefinitionFixedIncome::equals(const MktdataPayload& other) const {
    const auto* that = dynamic_cast<const MdInstrumentDefinitionFixedIncome*>(&other);
    return that != nullptr && *this == *that;
}

bool MdInstrumentDefinitionFixedIncome::operator==(const MdInstrumentDefinitionFixedIncome& other) const {
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
        && match_algorithm_ == other.match_algorithm_
        && min_trade_vol_ == other.min_trade_vol_
        && max_trade_vol_ == other.max_trade_vol_
        && min_price_increment_optional_ex_ == other.min_price_increment_optional_ex_
        && display_factor_ == other.display_factor_
        && main_fraction_ == other.main_fraction_
        && sub_fraction_ == other.sub_fraction_
        && price_display_format_ == other.price_display_format_
        && unit_of_measure_ == other.unit_of_measure_
        && unit_of_measure_qty_ == other.unit_of_measure_qty_
        && trading_reference_price_ == other.trading_reference_price_
        && trading_reference_date_ == other.trading_reference_date_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && min_price_increment_amount_ == other.min_price_increment_amount_
        && issue_date_ == other.issue_date_
        && dated_date_ == other.dated_date_
        && maturity_date_ == other.maturity_date_
        && coupon_rate_ == other.coupon_rate_
        && par_value_ == other.par_value_
        && coupon_frequency_unit_ == other.coupon_frequency_unit_
        && coupon_frequency_period_ == other.coupon_frequency_period_
        && coupon_day_count_ == other.coupon_day_count_
        && country_of_issue_ == other.country_of_issue_
        && issuer_ == other.issuer_
        && financial_instrument_full_name_ == other.financial_instrument_full_name_
        && security_alt_id_ == other.security_alt_id_
        && security_alt_id_source_ == other.security_alt_id_source_
        && price_quote_method_ == other.price_quote_method_
        && party_role_clearing_org_ == other.party_role_clearing_org_
        && user_defined_instrument_ == other.user_defined_instrument_
        && risk_set_ == other.risk_set_
        && market_set_ == other.market_set_
        && instrument_guid_ == other.instrument_guid_
        && events_groups_ == other.events_groups_
        && feed_types_groups_ == other.feed_types_groups_
        && inst_attrib_groups_ == other.inst_attrib_groups_
        && lot_type_rules_groups_ == other.lot_type_rules_groups_;
}

bool MdInstrumentDefinitionFixedIncome::operator!=(const MdInstrumentDefinitionFixedIncome& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
