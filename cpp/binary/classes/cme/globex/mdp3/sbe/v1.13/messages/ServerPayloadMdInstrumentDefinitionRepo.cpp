#include "ServerPayloadMdInstrumentDefinitionRepo.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

ServerPayloadMdInstrumentDefinitionRepo::ServerPayloadMdInstrumentDefinitionRepo(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const std::string& currency, const std::string& settl_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, Decimal min_price_increment_ex, Decimal display_factor, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> trading_reference_price, std::optional<std::uint16_t> trading_reference_date, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, const std::string& financial_instrument_full_name, const std::string& party_role_clearing_org, std::optional<std::uint16_t> start_date, std::optional<std::uint16_t> end_date, const std::string& termination_type, RepoSubType repo_sub_type, std::optional<MoneyOrPar> money_or_par, std::uint8_t max_no_of_substitutions, const std::string& price_quote_method, char user_defined_instrument, const std::string& risk_set, const std::string& market_set, std::optional<std::uint64_t> instrument_guid, const std::string& term_code, std::optional<std::uint8_t> broken_date_term_type, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups, const RepoUnderlyingsGroups& repo_underlyings_groups, const RepoRelatedInstrumentsGroups& repo_related_instruments_groups, const BrokenDatesGroups& broken_dates_groups)
  : match_event_indicator_(match_event_indicator), tot_num_reports_optional_(tot_num_reports_optional), security_update_action_(security_update_action), last_update_time_(last_update_time), md_security_trading_status_(md_security_trading_status), appl_id_(appl_id), market_segment_id_(market_segment_id), underlying_product_(underlying_product), security_exchange_(security_exchange), security_group_(security_group), asset_(asset), symbol_(symbol), security_id_(security_id), security_type_(security_type), cfi_code_(cfi_code), currency_(currency), settl_currency_(settl_currency), match_algorithm_(match_algorithm), min_trade_vol_(min_trade_vol), max_trade_vol_(max_trade_vol), min_price_increment_ex_(min_price_increment_ex), display_factor_(display_factor), unit_of_measure_(unit_of_measure), unit_of_measure_qty_(unit_of_measure_qty), trading_reference_price_(trading_reference_price), trading_reference_date_(trading_reference_date), high_limit_price_(high_limit_price), low_limit_price_(low_limit_price), max_price_variation_(max_price_variation), financial_instrument_full_name_(financial_instrument_full_name), party_role_clearing_org_(party_role_clearing_org), start_date_(start_date), end_date_(end_date), termination_type_(termination_type), repo_sub_type_(repo_sub_type), money_or_par_(money_or_par), max_no_of_substitutions_(max_no_of_substitutions), price_quote_method_(price_quote_method), user_defined_instrument_(user_defined_instrument), risk_set_(risk_set), market_set_(market_set), instrument_guid_(instrument_guid), term_code_(term_code), broken_date_term_type_(broken_date_term_type), events_groups_(events_groups), feed_types_groups_(feed_types_groups), inst_attrib_groups_(inst_attrib_groups), lot_type_rules_groups_(lot_type_rules_groups), repo_underlyings_groups_(repo_underlyings_groups), repo_related_instruments_groups_(repo_related_instruments_groups), broken_dates_groups_(broken_dates_groups) {}

const MatchEventIndicator& ServerPayloadMdInstrumentDefinitionRepo::match_event_indicator() const { return match_event_indicator_; }
MatchEventIndicator& ServerPayloadMdInstrumentDefinitionRepo::match_event_indicator() { return match_event_indicator_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_match_event_indicator(const MatchEventIndicator& value) { match_event_indicator_ = value; }

std::optional<std::uint32_t> ServerPayloadMdInstrumentDefinitionRepo::tot_num_reports_optional() const { return tot_num_reports_optional_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_tot_num_reports_optional(std::optional<std::uint32_t> value) { tot_num_reports_optional_ = value; }

SecurityUpdateAction ServerPayloadMdInstrumentDefinitionRepo::security_update_action() const { return security_update_action_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_security_update_action(SecurityUpdateAction value) { security_update_action_ = value; }

std::chrono::nanoseconds ServerPayloadMdInstrumentDefinitionRepo::last_update_time() const { return last_update_time_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_last_update_time(std::chrono::nanoseconds value) { last_update_time_ = value; }

std::optional<MdSecurityTradingStatus> ServerPayloadMdInstrumentDefinitionRepo::md_security_trading_status() const { return md_security_trading_status_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value) { md_security_trading_status_ = value; }

std::int16_t ServerPayloadMdInstrumentDefinitionRepo::appl_id() const { return appl_id_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_appl_id(std::int16_t value) { appl_id_ = value; }

std::uint8_t ServerPayloadMdInstrumentDefinitionRepo::market_segment_id() const { return market_segment_id_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_market_segment_id(std::uint8_t value) { market_segment_id_ = value; }

std::uint8_t ServerPayloadMdInstrumentDefinitionRepo::underlying_product() const { return underlying_product_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_underlying_product(std::uint8_t value) { underlying_product_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::security_exchange() const { return security_exchange_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::security_exchange() { return security_exchange_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_security_exchange(const std::string& value) { security_exchange_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::security_group() const { return security_group_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::security_group() { return security_group_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_security_group(const std::string& value) { security_group_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::asset() const { return asset_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::asset() { return asset_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_asset(const std::string& value) { asset_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::symbol() const { return symbol_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::symbol() { return symbol_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_symbol(const std::string& value) { symbol_ = value; }

std::int32_t ServerPayloadMdInstrumentDefinitionRepo::security_id() const { return security_id_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_security_id(std::int32_t value) { security_id_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::security_type() const { return security_type_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::security_type() { return security_type_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_security_type(const std::string& value) { security_type_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::cfi_code() const { return cfi_code_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::cfi_code() { return cfi_code_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_cfi_code(const std::string& value) { cfi_code_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::currency() const { return currency_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::currency() { return currency_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_currency(const std::string& value) { currency_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::settl_currency() const { return settl_currency_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::settl_currency() { return settl_currency_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_settl_currency(const std::string& value) { settl_currency_ = value; }

char ServerPayloadMdInstrumentDefinitionRepo::match_algorithm() const { return match_algorithm_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_match_algorithm(char value) { match_algorithm_ = value; }

std::uint32_t ServerPayloadMdInstrumentDefinitionRepo::min_trade_vol() const { return min_trade_vol_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_min_trade_vol(std::uint32_t value) { min_trade_vol_ = value; }

std::uint32_t ServerPayloadMdInstrumentDefinitionRepo::max_trade_vol() const { return max_trade_vol_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_max_trade_vol(std::uint32_t value) { max_trade_vol_ = value; }

Decimal ServerPayloadMdInstrumentDefinitionRepo::min_price_increment_ex() const { return min_price_increment_ex_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_min_price_increment_ex(Decimal value) { min_price_increment_ex_ = value; }

Decimal ServerPayloadMdInstrumentDefinitionRepo::display_factor() const { return display_factor_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_display_factor(Decimal value) { display_factor_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::unit_of_measure() const { return unit_of_measure_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::unit_of_measure() { return unit_of_measure_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_unit_of_measure(const std::string& value) { unit_of_measure_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionRepo::unit_of_measure_qty() const { return unit_of_measure_qty_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_unit_of_measure_qty(std::optional<Decimal> value) { unit_of_measure_qty_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionRepo::trading_reference_price() const { return trading_reference_price_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_trading_reference_price(std::optional<Decimal> value) { trading_reference_price_ = value; }

std::optional<std::uint16_t> ServerPayloadMdInstrumentDefinitionRepo::trading_reference_date() const { return trading_reference_date_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_trading_reference_date(std::optional<std::uint16_t> value) { trading_reference_date_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionRepo::high_limit_price() const { return high_limit_price_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_high_limit_price(std::optional<Decimal> value) { high_limit_price_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionRepo::low_limit_price() const { return low_limit_price_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_low_limit_price(std::optional<Decimal> value) { low_limit_price_ = value; }

std::optional<Decimal> ServerPayloadMdInstrumentDefinitionRepo::max_price_variation() const { return max_price_variation_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_max_price_variation(std::optional<Decimal> value) { max_price_variation_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::financial_instrument_full_name() const { return financial_instrument_full_name_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::financial_instrument_full_name() { return financial_instrument_full_name_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_financial_instrument_full_name(const std::string& value) { financial_instrument_full_name_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::party_role_clearing_org() const { return party_role_clearing_org_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::party_role_clearing_org() { return party_role_clearing_org_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_party_role_clearing_org(const std::string& value) { party_role_clearing_org_ = value; }

std::optional<std::uint16_t> ServerPayloadMdInstrumentDefinitionRepo::start_date() const { return start_date_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_start_date(std::optional<std::uint16_t> value) { start_date_ = value; }

std::optional<std::uint16_t> ServerPayloadMdInstrumentDefinitionRepo::end_date() const { return end_date_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_end_date(std::optional<std::uint16_t> value) { end_date_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::termination_type() const { return termination_type_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::termination_type() { return termination_type_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_termination_type(const std::string& value) { termination_type_ = value; }

RepoSubType ServerPayloadMdInstrumentDefinitionRepo::repo_sub_type() const { return repo_sub_type_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_repo_sub_type(RepoSubType value) { repo_sub_type_ = value; }

std::optional<MoneyOrPar> ServerPayloadMdInstrumentDefinitionRepo::money_or_par() const { return money_or_par_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_money_or_par(std::optional<MoneyOrPar> value) { money_or_par_ = value; }

std::uint8_t ServerPayloadMdInstrumentDefinitionRepo::max_no_of_substitutions() const { return max_no_of_substitutions_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_max_no_of_substitutions(std::uint8_t value) { max_no_of_substitutions_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::price_quote_method() const { return price_quote_method_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::price_quote_method() { return price_quote_method_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_price_quote_method(const std::string& value) { price_quote_method_ = value; }

char ServerPayloadMdInstrumentDefinitionRepo::user_defined_instrument() const { return user_defined_instrument_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_user_defined_instrument(char value) { user_defined_instrument_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::risk_set() const { return risk_set_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::risk_set() { return risk_set_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_risk_set(const std::string& value) { risk_set_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::market_set() const { return market_set_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::market_set() { return market_set_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_market_set(const std::string& value) { market_set_ = value; }

std::optional<std::uint64_t> ServerPayloadMdInstrumentDefinitionRepo::instrument_guid() const { return instrument_guid_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_instrument_guid(std::optional<std::uint64_t> value) { instrument_guid_ = value; }

const std::string& ServerPayloadMdInstrumentDefinitionRepo::term_code() const { return term_code_; }
std::string& ServerPayloadMdInstrumentDefinitionRepo::term_code() { return term_code_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_term_code(const std::string& value) { term_code_ = value; }

std::optional<std::uint8_t> ServerPayloadMdInstrumentDefinitionRepo::broken_date_term_type() const { return broken_date_term_type_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_broken_date_term_type(std::optional<std::uint8_t> value) { broken_date_term_type_ = value; }

const EventsGroups& ServerPayloadMdInstrumentDefinitionRepo::events_groups() const { return events_groups_; }
EventsGroups& ServerPayloadMdInstrumentDefinitionRepo::events_groups() { return events_groups_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_events_groups(const EventsGroups& value) { events_groups_ = value; }

const FeedTypesGroups& ServerPayloadMdInstrumentDefinitionRepo::feed_types_groups() const { return feed_types_groups_; }
FeedTypesGroups& ServerPayloadMdInstrumentDefinitionRepo::feed_types_groups() { return feed_types_groups_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_feed_types_groups(const FeedTypesGroups& value) { feed_types_groups_ = value; }

const InstAttribGroups& ServerPayloadMdInstrumentDefinitionRepo::inst_attrib_groups() const { return inst_attrib_groups_; }
InstAttribGroups& ServerPayloadMdInstrumentDefinitionRepo::inst_attrib_groups() { return inst_attrib_groups_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_inst_attrib_groups(const InstAttribGroups& value) { inst_attrib_groups_ = value; }

const LotTypeRulesGroups& ServerPayloadMdInstrumentDefinitionRepo::lot_type_rules_groups() const { return lot_type_rules_groups_; }
LotTypeRulesGroups& ServerPayloadMdInstrumentDefinitionRepo::lot_type_rules_groups() { return lot_type_rules_groups_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_lot_type_rules_groups(const LotTypeRulesGroups& value) { lot_type_rules_groups_ = value; }

const RepoUnderlyingsGroups& ServerPayloadMdInstrumentDefinitionRepo::repo_underlyings_groups() const { return repo_underlyings_groups_; }
RepoUnderlyingsGroups& ServerPayloadMdInstrumentDefinitionRepo::repo_underlyings_groups() { return repo_underlyings_groups_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_repo_underlyings_groups(const RepoUnderlyingsGroups& value) { repo_underlyings_groups_ = value; }

const RepoRelatedInstrumentsGroups& ServerPayloadMdInstrumentDefinitionRepo::repo_related_instruments_groups() const { return repo_related_instruments_groups_; }
RepoRelatedInstrumentsGroups& ServerPayloadMdInstrumentDefinitionRepo::repo_related_instruments_groups() { return repo_related_instruments_groups_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_repo_related_instruments_groups(const RepoRelatedInstrumentsGroups& value) { repo_related_instruments_groups_ = value; }

const BrokenDatesGroups& ServerPayloadMdInstrumentDefinitionRepo::broken_dates_groups() const { return broken_dates_groups_; }
BrokenDatesGroups& ServerPayloadMdInstrumentDefinitionRepo::broken_dates_groups() { return broken_dates_groups_; }
void ServerPayloadMdInstrumentDefinitionRepo::set_broken_dates_groups(const BrokenDatesGroups& value) { broken_dates_groups_ = value; }

ServerTcpMessageCode ServerPayloadMdInstrumentDefinitionRepo::type() const { return message_type; }

std::string_view ServerPayloadMdInstrumentDefinitionRepo::name() const { return "Md Instrument Definition Repo"; }

std::size_t ServerPayloadMdInstrumentDefinitionRepo::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    offset += match_event_indicator_.decode(data + offset, length - offset);

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 4, length);
    tot_num_reports_optional_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(4294967295ULL));
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    security_update_action_ = static_cast<SecurityUpdateAction>(wire::read_char(data + offset));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    last_update_time_ = std::chrono::nanoseconds(static_cast<std::int64_t>(wire::read_u64_le(data + offset)));
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    md_security_trading_status_ = wire::nullable_enum<MdSecurityTradingStatus>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 2, length);
    appl_id_ = wire::read_i16_le(data + offset);
    offset += 2;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    market_segment_id_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    underlying_product_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 4, length);
    security_exchange_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 6, length);
    security_group_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 6, length);
    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 20, length);
    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 4, length);
    security_id_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 6, length);
    security_type_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 6, length);
    cfi_code_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 3, length);
    currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 3, length);
    settl_currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    match_algorithm_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 4, length);
    min_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 4, length);
    max_trade_vol_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    min_price_increment_ex_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    display_factor_ = Decimal(static_cast<std::int64_t>(wire::read_i64_le(data + offset)), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 30, length);
    unit_of_measure_ = wire::read_text(data + offset, 30, '\0');
    offset += 30;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    unit_of_measure_qty_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    trading_reference_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 2, length);
    trading_reference_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    high_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    low_limit_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    max_price_variation_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(9223372036854775807LL), -9);
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 35, length);
    financial_instrument_full_name_ = wire::read_text(data + offset, 35, '\0');
    offset += 35;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 5, length);
    party_role_clearing_org_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 2, length);
    start_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 2, length);
    end_date_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    termination_type_ = wire::read_text(data + offset, 8, '\0');
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    repo_sub_type_ = static_cast<RepoSubType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    money_or_par_ = wire::nullable_enum<MoneyOrPar>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    max_no_of_substitutions_ = wire::read_u8(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 5, length);
    price_quote_method_ = wire::read_text(data + offset, 5, '\0');
    offset += 5;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    user_defined_instrument_ = wire::read_char(data + offset);
    offset += 1;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 6, length);
    risk_set_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 6, length);
    market_set_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 8, length);
    instrument_guid_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(18446744073709551615ULL));
    offset += 8;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 20, length);
    term_code_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("ServerPayloadMdInstrumentDefinitionRepo", offset + 1, length);
    broken_date_term_type_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    offset += events_groups_.decode(data + offset, length - offset);

    offset += feed_types_groups_.decode(data + offset, length - offset);

    offset += inst_attrib_groups_.decode(data + offset, length - offset);

    offset += lot_type_rules_groups_.decode(data + offset, length - offset);

    offset += repo_underlyings_groups_.decode(data + offset, length - offset);

    offset += repo_related_instruments_groups_.decode(data + offset, length - offset);

    offset += broken_dates_groups_.decode(data + offset, length - offset);

    return offset;
}

std::size_t ServerPayloadMdInstrumentDefinitionRepo::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("ServerPayloadMdInstrumentDefinitionRepo", encoded_size(), capacity);

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

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(min_price_increment_ex_.mantissa()));
    offset += 8;

    wire::write_i64_le(data + offset, static_cast<std::int64_t>(display_factor_.mantissa()));
    offset += 8;

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

    wire::write_text(data + offset, 35, '\0', financial_instrument_full_name_);
    offset += 35;

    wire::write_text(data + offset, 5, '\0', party_role_clearing_org_);
    offset += 5;

    wire::write_u16_le(data + offset, start_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_u16_le(data + offset, end_date_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_text(data + offset, 8, '\0', termination_type_);
    offset += 8;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(repo_sub_type_));
    offset += 1;

    wire::write_u8(data + offset, money_or_par_ ? static_cast<std::uint8_t>(*money_or_par_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(max_no_of_substitutions_));
    offset += 1;

    wire::write_text(data + offset, 5, '\0', price_quote_method_);
    offset += 5;

    wire::write_char(data + offset, user_defined_instrument_);
    offset += 1;

    wire::write_text(data + offset, 6, '\0', risk_set_);
    offset += 6;

    wire::write_text(data + offset, 6, '\0', market_set_);
    offset += 6;

    wire::write_u64_le(data + offset, instrument_guid_.value_or(static_cast<std::uint64_t>(18446744073709551615ULL)));
    offset += 8;

    wire::write_text(data + offset, 20, '\0', term_code_);
    offset += 20;

    wire::write_u8(data + offset, broken_date_term_type_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    offset += events_groups_.encode(data + offset, capacity - offset);

    offset += feed_types_groups_.encode(data + offset, capacity - offset);

    offset += inst_attrib_groups_.encode(data + offset, capacity - offset);

    offset += lot_type_rules_groups_.encode(data + offset, capacity - offset);

    offset += repo_underlyings_groups_.encode(data + offset, capacity - offset);

    offset += repo_related_instruments_groups_.encode(data + offset, capacity - offset);

    offset += broken_dates_groups_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t ServerPayloadMdInstrumentDefinitionRepo::encoded_size() const {
    return match_event_indicator_.encoded_size() + 4 + 1 + 8 + 1 + 2 + 1 + 1 + 4 + 6 + 6 + 20 + 4 + 6 + 6 + 3 + 3 + 1 + 4 + 4 + 8 + 8 + 30 + 8 + 8 + 2 + 8 + 8 + 8 + 35 + 5 + 2 + 2 + 8 + 1 + 1 + 1 + 5 + 1 + 6 + 6 + 8 + 20 + 1 + events_groups_.encoded_size() + feed_types_groups_.encoded_size() + inst_attrib_groups_.encoded_size() + lot_type_rules_groups_.encoded_size() + repo_underlyings_groups_.encoded_size() + repo_related_instruments_groups_.encoded_size() + broken_dates_groups_.encoded_size();
}

void ServerPayloadMdInstrumentDefinitionRepo::accept(ServerTcpMessageVisitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<ServerTcpMessage> ServerPayloadMdInstrumentDefinitionRepo::clone() const {
    return std::make_unique<ServerPayloadMdInstrumentDefinitionRepo>(*this);
}

void ServerPayloadMdInstrumentDefinitionRepo::print(std::ostream& out) const {
    out << "ServerPayloadMdInstrumentDefinitionRepo{";
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
    out << ", min_price_increment_ex=";
    out << min_price_increment_ex_;
    out << ", display_factor=";
    out << display_factor_;
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
    out << ", financial_instrument_full_name=";
    print::text(out, financial_instrument_full_name_);
    out << ", party_role_clearing_org=";
    print::text(out, party_role_clearing_org_);
    out << ", start_date=";
    print::optional(out, start_date_);
    out << ", end_date=";
    print::optional(out, end_date_);
    out << ", termination_type=";
    print::text(out, termination_type_);
    out << ", repo_sub_type=";
    out << repo_sub_type_;
    out << ", money_or_par=";
    print::optional(out, money_or_par_);
    out << ", max_no_of_substitutions=";
    out << static_cast<int>(max_no_of_substitutions_);
    out << ", price_quote_method=";
    print::text(out, price_quote_method_);
    out << ", user_defined_instrument=";
    print::character(out, user_defined_instrument_);
    out << ", risk_set=";
    print::text(out, risk_set_);
    out << ", market_set=";
    print::text(out, market_set_);
    out << ", instrument_guid=";
    print::optional(out, instrument_guid_);
    out << ", term_code=";
    print::text(out, term_code_);
    out << ", broken_date_term_type=";
    print::optional(out, broken_date_term_type_);
    out << ", events_groups=";
    events_groups_.print(out);
    out << ", feed_types_groups=";
    feed_types_groups_.print(out);
    out << ", inst_attrib_groups=";
    inst_attrib_groups_.print(out);
    out << ", lot_type_rules_groups=";
    lot_type_rules_groups_.print(out);
    out << ", repo_underlyings_groups=";
    repo_underlyings_groups_.print(out);
    out << ", repo_related_instruments_groups=";
    repo_related_instruments_groups_.print(out);
    out << ", broken_dates_groups=";
    broken_dates_groups_.print(out);
    out << '}';
}

bool ServerPayloadMdInstrumentDefinitionRepo::equals(const ServerTcpMessage& other) const {
    const auto* that = dynamic_cast<const ServerPayloadMdInstrumentDefinitionRepo*>(&other);
    return that != nullptr && *this == *that;
}

bool ServerPayloadMdInstrumentDefinitionRepo::operator==(const ServerPayloadMdInstrumentDefinitionRepo& other) const {
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
        && min_price_increment_ex_ == other.min_price_increment_ex_
        && display_factor_ == other.display_factor_
        && unit_of_measure_ == other.unit_of_measure_
        && unit_of_measure_qty_ == other.unit_of_measure_qty_
        && trading_reference_price_ == other.trading_reference_price_
        && trading_reference_date_ == other.trading_reference_date_
        && high_limit_price_ == other.high_limit_price_
        && low_limit_price_ == other.low_limit_price_
        && max_price_variation_ == other.max_price_variation_
        && financial_instrument_full_name_ == other.financial_instrument_full_name_
        && party_role_clearing_org_ == other.party_role_clearing_org_
        && start_date_ == other.start_date_
        && end_date_ == other.end_date_
        && termination_type_ == other.termination_type_
        && repo_sub_type_ == other.repo_sub_type_
        && money_or_par_ == other.money_or_par_
        && max_no_of_substitutions_ == other.max_no_of_substitutions_
        && price_quote_method_ == other.price_quote_method_
        && user_defined_instrument_ == other.user_defined_instrument_
        && risk_set_ == other.risk_set_
        && market_set_ == other.market_set_
        && instrument_guid_ == other.instrument_guid_
        && term_code_ == other.term_code_
        && broken_date_term_type_ == other.broken_date_term_type_
        && events_groups_ == other.events_groups_
        && feed_types_groups_ == other.feed_types_groups_
        && inst_attrib_groups_ == other.inst_attrib_groups_
        && lot_type_rules_groups_ == other.lot_type_rules_groups_
        && repo_underlyings_groups_ == other.repo_underlyings_groups_
        && repo_related_instruments_groups_ == other.repo_related_instruments_groups_
        && broken_dates_groups_ == other.broken_dates_groups_;
}

bool ServerPayloadMdInstrumentDefinitionRepo::operator!=(const ServerPayloadMdInstrumentDefinitionRepo& other) const {
    return !(*this == other);
}

} // namespace cme::globex::mdp3::sbe::v1_13
