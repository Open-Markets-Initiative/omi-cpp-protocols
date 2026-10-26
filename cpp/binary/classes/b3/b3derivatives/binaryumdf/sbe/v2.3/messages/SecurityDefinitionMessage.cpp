#include "SecurityDefinitionMessage.hpp"

#include "../common/Print.hpp"
#include "../common/Wire.hpp"
#include "../Visitor.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

SecurityDefinitionMessage::SecurityDefinitionMessage(std::uint64_t security_id, const std::string& security_exchange, SecurityIdSource security_id_source, const std::string& security_group, const std::string& symbol, SecurityUpdateAction security_update_action, SecurityType security_type, std::uint16_t security_sub_type, std::uint32_t tot_no_related_sym, std::optional<Decimal> min_price_increment, std::optional<Decimal> strike_price, std::optional<Decimal> contract_multiplier, std::optional<Decimal> price_divisor, std::optional<std::int64_t> security_validity_timestamp, std::optional<std::uint64_t> no_shares_issued, std::optional<std::uint64_t> clearing_house_id, std::optional<std::int64_t> min_order_qty, std::optional<std::int64_t> max_order_qty, std::optional<std::int64_t> min_lot_size, std::optional<std::int64_t> min_trade_vol, std::optional<std::uint32_t> corporate_action_event_id, std::int32_t issue_date, std::optional<std::int32_t> maturity_date, const std::string& country_of_issue, std::optional<std::int32_t> start_date, std::optional<std::int32_t> end_date, std::optional<std::uint16_t> settl_type, std::optional<std::int32_t> settl_date_local_mkt_date_32_optional, std::optional<std::int32_t> dated_date, const std::string& isin_number, const std::string& asset, const std::string& cfi_code, const MaturityMonthYear& maturity_month_year, const ContractSettlMonth& contract_settl_month, const std::string& currency, const std::string& strike_currency, const std::string& settl_currency, const std::string& security_strategy_type, std::optional<LotType> lot_type, std::optional<std::uint8_t> tick_size_denominator, Product product, std::optional<ExerciseStyle> exercise_style, std::optional<PutOrCall> put_or_call, std::optional<PriceTypeOptional> price_type_optional, std::optional<std::uint8_t> market_segment_id, std::optional<GovernanceIndicator> governance_indicator, std::optional<SecurityMatchType> security_match_type, std::optional<LastFragment> last_fragment, std::optional<MultiLegModel> multi_leg_model, std::optional<MultiLegPriceMethod> multi_leg_price_method, std::optional<std::int64_t> min_cross_qty, std::optional<ImpliedMarketIndicator> implied_market_indicator, std::optional<OptPayoutType> opt_payout_type, const UnderlyingsGroups& underlyings_groups, const LegsGroups& legs_groups, const InstrAttribsGroups& instr_attribs_groups, const SecurityDesc& security_desc)
  : security_id_(security_id), security_exchange_(security_exchange), security_id_source_(security_id_source), security_group_(security_group), symbol_(symbol), security_update_action_(security_update_action), security_type_(security_type), security_sub_type_(security_sub_type), tot_no_related_sym_(tot_no_related_sym), min_price_increment_(min_price_increment), strike_price_(strike_price), contract_multiplier_(contract_multiplier), price_divisor_(price_divisor), security_validity_timestamp_(security_validity_timestamp), no_shares_issued_(no_shares_issued), clearing_house_id_(clearing_house_id), min_order_qty_(min_order_qty), max_order_qty_(max_order_qty), min_lot_size_(min_lot_size), min_trade_vol_(min_trade_vol), corporate_action_event_id_(corporate_action_event_id), issue_date_(issue_date), maturity_date_(maturity_date), country_of_issue_(country_of_issue), start_date_(start_date), end_date_(end_date), settl_type_(settl_type), settl_date_local_mkt_date_32_optional_(settl_date_local_mkt_date_32_optional), dated_date_(dated_date), isin_number_(isin_number), asset_(asset), cfi_code_(cfi_code), maturity_month_year_(maturity_month_year), contract_settl_month_(contract_settl_month), currency_(currency), strike_currency_(strike_currency), settl_currency_(settl_currency), security_strategy_type_(security_strategy_type), lot_type_(lot_type), tick_size_denominator_(tick_size_denominator), product_(product), exercise_style_(exercise_style), put_or_call_(put_or_call), price_type_optional_(price_type_optional), market_segment_id_(market_segment_id), governance_indicator_(governance_indicator), security_match_type_(security_match_type), last_fragment_(last_fragment), multi_leg_model_(multi_leg_model), multi_leg_price_method_(multi_leg_price_method), min_cross_qty_(min_cross_qty), implied_market_indicator_(implied_market_indicator), opt_payout_type_(opt_payout_type), underlyings_groups_(underlyings_groups), legs_groups_(legs_groups), instr_attribs_groups_(instr_attribs_groups), security_desc_(security_desc) {}

std::uint64_t SecurityDefinitionMessage::security_id() const { return security_id_; }
void SecurityDefinitionMessage::set_security_id(std::uint64_t value) { security_id_ = value; }

const std::string& SecurityDefinitionMessage::security_exchange() const { return security_exchange_; }
std::string& SecurityDefinitionMessage::security_exchange() { return security_exchange_; }
void SecurityDefinitionMessage::set_security_exchange(const std::string& value) { security_exchange_ = value; }

SecurityIdSource SecurityDefinitionMessage::security_id_source() const { return security_id_source_; }
void SecurityDefinitionMessage::set_security_id_source(SecurityIdSource value) { security_id_source_ = value; }

const std::string& SecurityDefinitionMessage::security_group() const { return security_group_; }
std::string& SecurityDefinitionMessage::security_group() { return security_group_; }
void SecurityDefinitionMessage::set_security_group(const std::string& value) { security_group_ = value; }

const std::string& SecurityDefinitionMessage::symbol() const { return symbol_; }
std::string& SecurityDefinitionMessage::symbol() { return symbol_; }
void SecurityDefinitionMessage::set_symbol(const std::string& value) { symbol_ = value; }

SecurityUpdateAction SecurityDefinitionMessage::security_update_action() const { return security_update_action_; }
void SecurityDefinitionMessage::set_security_update_action(SecurityUpdateAction value) { security_update_action_ = value; }

SecurityType SecurityDefinitionMessage::security_type() const { return security_type_; }
void SecurityDefinitionMessage::set_security_type(SecurityType value) { security_type_ = value; }

std::uint16_t SecurityDefinitionMessage::security_sub_type() const { return security_sub_type_; }
void SecurityDefinitionMessage::set_security_sub_type(std::uint16_t value) { security_sub_type_ = value; }

std::uint32_t SecurityDefinitionMessage::tot_no_related_sym() const { return tot_no_related_sym_; }
void SecurityDefinitionMessage::set_tot_no_related_sym(std::uint32_t value) { tot_no_related_sym_ = value; }

std::optional<Decimal> SecurityDefinitionMessage::min_price_increment() const { return min_price_increment_; }
void SecurityDefinitionMessage::set_min_price_increment(std::optional<Decimal> value) { min_price_increment_ = value; }

std::optional<Decimal> SecurityDefinitionMessage::strike_price() const { return strike_price_; }
void SecurityDefinitionMessage::set_strike_price(std::optional<Decimal> value) { strike_price_ = value; }

std::optional<Decimal> SecurityDefinitionMessage::contract_multiplier() const { return contract_multiplier_; }
void SecurityDefinitionMessage::set_contract_multiplier(std::optional<Decimal> value) { contract_multiplier_ = value; }

std::optional<Decimal> SecurityDefinitionMessage::price_divisor() const { return price_divisor_; }
void SecurityDefinitionMessage::set_price_divisor(std::optional<Decimal> value) { price_divisor_ = value; }

std::optional<std::int64_t> SecurityDefinitionMessage::security_validity_timestamp() const { return security_validity_timestamp_; }
void SecurityDefinitionMessage::set_security_validity_timestamp(std::optional<std::int64_t> value) { security_validity_timestamp_ = value; }

std::optional<std::uint64_t> SecurityDefinitionMessage::no_shares_issued() const { return no_shares_issued_; }
void SecurityDefinitionMessage::set_no_shares_issued(std::optional<std::uint64_t> value) { no_shares_issued_ = value; }

std::optional<std::uint64_t> SecurityDefinitionMessage::clearing_house_id() const { return clearing_house_id_; }
void SecurityDefinitionMessage::set_clearing_house_id(std::optional<std::uint64_t> value) { clearing_house_id_ = value; }

std::optional<std::int64_t> SecurityDefinitionMessage::min_order_qty() const { return min_order_qty_; }
void SecurityDefinitionMessage::set_min_order_qty(std::optional<std::int64_t> value) { min_order_qty_ = value; }

std::optional<std::int64_t> SecurityDefinitionMessage::max_order_qty() const { return max_order_qty_; }
void SecurityDefinitionMessage::set_max_order_qty(std::optional<std::int64_t> value) { max_order_qty_ = value; }

std::optional<std::int64_t> SecurityDefinitionMessage::min_lot_size() const { return min_lot_size_; }
void SecurityDefinitionMessage::set_min_lot_size(std::optional<std::int64_t> value) { min_lot_size_ = value; }

std::optional<std::int64_t> SecurityDefinitionMessage::min_trade_vol() const { return min_trade_vol_; }
void SecurityDefinitionMessage::set_min_trade_vol(std::optional<std::int64_t> value) { min_trade_vol_ = value; }

std::optional<std::uint32_t> SecurityDefinitionMessage::corporate_action_event_id() const { return corporate_action_event_id_; }
void SecurityDefinitionMessage::set_corporate_action_event_id(std::optional<std::uint32_t> value) { corporate_action_event_id_ = value; }

std::int32_t SecurityDefinitionMessage::issue_date() const { return issue_date_; }
void SecurityDefinitionMessage::set_issue_date(std::int32_t value) { issue_date_ = value; }

std::optional<std::int32_t> SecurityDefinitionMessage::maturity_date() const { return maturity_date_; }
void SecurityDefinitionMessage::set_maturity_date(std::optional<std::int32_t> value) { maturity_date_ = value; }

const std::string& SecurityDefinitionMessage::country_of_issue() const { return country_of_issue_; }
std::string& SecurityDefinitionMessage::country_of_issue() { return country_of_issue_; }
void SecurityDefinitionMessage::set_country_of_issue(const std::string& value) { country_of_issue_ = value; }

std::optional<std::int32_t> SecurityDefinitionMessage::start_date() const { return start_date_; }
void SecurityDefinitionMessage::set_start_date(std::optional<std::int32_t> value) { start_date_ = value; }

std::optional<std::int32_t> SecurityDefinitionMessage::end_date() const { return end_date_; }
void SecurityDefinitionMessage::set_end_date(std::optional<std::int32_t> value) { end_date_ = value; }

std::optional<std::uint16_t> SecurityDefinitionMessage::settl_type() const { return settl_type_; }
void SecurityDefinitionMessage::set_settl_type(std::optional<std::uint16_t> value) { settl_type_ = value; }

std::optional<std::int32_t> SecurityDefinitionMessage::settl_date_local_mkt_date_32_optional() const { return settl_date_local_mkt_date_32_optional_; }
void SecurityDefinitionMessage::set_settl_date_local_mkt_date_32_optional(std::optional<std::int32_t> value) { settl_date_local_mkt_date_32_optional_ = value; }

std::optional<std::int32_t> SecurityDefinitionMessage::dated_date() const { return dated_date_; }
void SecurityDefinitionMessage::set_dated_date(std::optional<std::int32_t> value) { dated_date_ = value; }

const std::string& SecurityDefinitionMessage::isin_number() const { return isin_number_; }
std::string& SecurityDefinitionMessage::isin_number() { return isin_number_; }
void SecurityDefinitionMessage::set_isin_number(const std::string& value) { isin_number_ = value; }

const std::string& SecurityDefinitionMessage::asset() const { return asset_; }
std::string& SecurityDefinitionMessage::asset() { return asset_; }
void SecurityDefinitionMessage::set_asset(const std::string& value) { asset_ = value; }

const std::string& SecurityDefinitionMessage::cfi_code() const { return cfi_code_; }
std::string& SecurityDefinitionMessage::cfi_code() { return cfi_code_; }
void SecurityDefinitionMessage::set_cfi_code(const std::string& value) { cfi_code_ = value; }

const MaturityMonthYear& SecurityDefinitionMessage::maturity_month_year() const { return maturity_month_year_; }
MaturityMonthYear& SecurityDefinitionMessage::maturity_month_year() { return maturity_month_year_; }
void SecurityDefinitionMessage::set_maturity_month_year(const MaturityMonthYear& value) { maturity_month_year_ = value; }

const ContractSettlMonth& SecurityDefinitionMessage::contract_settl_month() const { return contract_settl_month_; }
ContractSettlMonth& SecurityDefinitionMessage::contract_settl_month() { return contract_settl_month_; }
void SecurityDefinitionMessage::set_contract_settl_month(const ContractSettlMonth& value) { contract_settl_month_ = value; }

const std::string& SecurityDefinitionMessage::currency() const { return currency_; }
std::string& SecurityDefinitionMessage::currency() { return currency_; }
void SecurityDefinitionMessage::set_currency(const std::string& value) { currency_ = value; }

const std::string& SecurityDefinitionMessage::strike_currency() const { return strike_currency_; }
std::string& SecurityDefinitionMessage::strike_currency() { return strike_currency_; }
void SecurityDefinitionMessage::set_strike_currency(const std::string& value) { strike_currency_ = value; }

const std::string& SecurityDefinitionMessage::settl_currency() const { return settl_currency_; }
std::string& SecurityDefinitionMessage::settl_currency() { return settl_currency_; }
void SecurityDefinitionMessage::set_settl_currency(const std::string& value) { settl_currency_ = value; }

const std::string& SecurityDefinitionMessage::security_strategy_type() const { return security_strategy_type_; }
std::string& SecurityDefinitionMessage::security_strategy_type() { return security_strategy_type_; }
void SecurityDefinitionMessage::set_security_strategy_type(const std::string& value) { security_strategy_type_ = value; }

std::optional<LotType> SecurityDefinitionMessage::lot_type() const { return lot_type_; }
void SecurityDefinitionMessage::set_lot_type(std::optional<LotType> value) { lot_type_ = value; }

std::optional<std::uint8_t> SecurityDefinitionMessage::tick_size_denominator() const { return tick_size_denominator_; }
void SecurityDefinitionMessage::set_tick_size_denominator(std::optional<std::uint8_t> value) { tick_size_denominator_ = value; }

Product SecurityDefinitionMessage::product() const { return product_; }
void SecurityDefinitionMessage::set_product(Product value) { product_ = value; }

std::optional<ExerciseStyle> SecurityDefinitionMessage::exercise_style() const { return exercise_style_; }
void SecurityDefinitionMessage::set_exercise_style(std::optional<ExerciseStyle> value) { exercise_style_ = value; }

std::optional<PutOrCall> SecurityDefinitionMessage::put_or_call() const { return put_or_call_; }
void SecurityDefinitionMessage::set_put_or_call(std::optional<PutOrCall> value) { put_or_call_ = value; }

std::optional<PriceTypeOptional> SecurityDefinitionMessage::price_type_optional() const { return price_type_optional_; }
void SecurityDefinitionMessage::set_price_type_optional(std::optional<PriceTypeOptional> value) { price_type_optional_ = value; }

std::optional<std::uint8_t> SecurityDefinitionMessage::market_segment_id() const { return market_segment_id_; }
void SecurityDefinitionMessage::set_market_segment_id(std::optional<std::uint8_t> value) { market_segment_id_ = value; }

std::optional<GovernanceIndicator> SecurityDefinitionMessage::governance_indicator() const { return governance_indicator_; }
void SecurityDefinitionMessage::set_governance_indicator(std::optional<GovernanceIndicator> value) { governance_indicator_ = value; }

std::optional<SecurityMatchType> SecurityDefinitionMessage::security_match_type() const { return security_match_type_; }
void SecurityDefinitionMessage::set_security_match_type(std::optional<SecurityMatchType> value) { security_match_type_ = value; }

std::optional<LastFragment> SecurityDefinitionMessage::last_fragment() const { return last_fragment_; }
void SecurityDefinitionMessage::set_last_fragment(std::optional<LastFragment> value) { last_fragment_ = value; }

std::optional<MultiLegModel> SecurityDefinitionMessage::multi_leg_model() const { return multi_leg_model_; }
void SecurityDefinitionMessage::set_multi_leg_model(std::optional<MultiLegModel> value) { multi_leg_model_ = value; }

std::optional<MultiLegPriceMethod> SecurityDefinitionMessage::multi_leg_price_method() const { return multi_leg_price_method_; }
void SecurityDefinitionMessage::set_multi_leg_price_method(std::optional<MultiLegPriceMethod> value) { multi_leg_price_method_ = value; }

std::optional<std::int64_t> SecurityDefinitionMessage::min_cross_qty() const { return min_cross_qty_; }
void SecurityDefinitionMessage::set_min_cross_qty(std::optional<std::int64_t> value) { min_cross_qty_ = value; }

std::optional<ImpliedMarketIndicator> SecurityDefinitionMessage::implied_market_indicator() const { return implied_market_indicator_; }
void SecurityDefinitionMessage::set_implied_market_indicator(std::optional<ImpliedMarketIndicator> value) { implied_market_indicator_ = value; }

std::optional<OptPayoutType> SecurityDefinitionMessage::opt_payout_type() const { return opt_payout_type_; }
void SecurityDefinitionMessage::set_opt_payout_type(std::optional<OptPayoutType> value) { opt_payout_type_ = value; }

const UnderlyingsGroups& SecurityDefinitionMessage::underlyings_groups() const { return underlyings_groups_; }
UnderlyingsGroups& SecurityDefinitionMessage::underlyings_groups() { return underlyings_groups_; }
void SecurityDefinitionMessage::set_underlyings_groups(const UnderlyingsGroups& value) { underlyings_groups_ = value; }

const LegsGroups& SecurityDefinitionMessage::legs_groups() const { return legs_groups_; }
LegsGroups& SecurityDefinitionMessage::legs_groups() { return legs_groups_; }
void SecurityDefinitionMessage::set_legs_groups(const LegsGroups& value) { legs_groups_ = value; }

const InstrAttribsGroups& SecurityDefinitionMessage::instr_attribs_groups() const { return instr_attribs_groups_; }
InstrAttribsGroups& SecurityDefinitionMessage::instr_attribs_groups() { return instr_attribs_groups_; }
void SecurityDefinitionMessage::set_instr_attribs_groups(const InstrAttribsGroups& value) { instr_attribs_groups_ = value; }

const SecurityDesc& SecurityDefinitionMessage::security_desc() const { return security_desc_; }
SecurityDesc& SecurityDefinitionMessage::security_desc() { return security_desc_; }
void SecurityDefinitionMessage::set_security_desc(const SecurityDesc& value) { security_desc_ = value; }

MessageCode SecurityDefinitionMessage::type() const { return message_type; }

std::string_view SecurityDefinitionMessage::name() const { return "Security Definition Message"; }

std::size_t SecurityDefinitionMessage::decode(const std::byte* data, std::size_t length) {
    std::size_t offset = 0;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    security_id_ = wire::read_u64_le(data + offset);
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    security_exchange_ = wire::read_text(data + offset, 4, '\0');
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    security_id_source_ = static_cast<SecurityIdSource>(wire::read_char(data + offset));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 3, length);
    security_group_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("SecurityDefinitionMessage", offset + 20, length);
    symbol_ = wire::read_text(data + offset, 20, '\0');
    offset += 20;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    security_update_action_ = static_cast<SecurityUpdateAction>(wire::read_char(data + offset));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    security_type_ = static_cast<SecurityType>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 2, length);
    security_sub_type_ = wire::read_u16_le(data + offset);
    offset += 2;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    tot_no_related_sym_ = wire::read_u32_le(data + offset);
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    min_price_increment_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    strike_price_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -4);
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    contract_multiplier_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    price_divisor_ = wire::nullable_decimal(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1), -8);
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    security_validity_timestamp_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    no_shares_issued_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    clearing_house_id_ = wire::nullable(wire::read_u64_le(data + offset), static_cast<std::uint64_t>(0ULL));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    min_order_qty_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    max_order_qty_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    min_lot_size_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    min_trade_vol_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    corporate_action_event_id_ = wire::nullable(wire::read_u32_le(data + offset), static_cast<std::uint32_t>(0ULL));
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    issue_date_ = wire::read_i32_le(data + offset);
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    maturity_date_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 2, length);
    country_of_issue_ = wire::read_text(data + offset, 2, '\0');
    offset += 2;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    start_date_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    end_date_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 2, length);
    settl_type_ = wire::nullable(wire::read_u16_le(data + offset), static_cast<std::uint16_t>(65535ULL));
    offset += 2;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    settl_date_local_mkt_date_32_optional_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 4, length);
    dated_date_ = wire::nullable(wire::read_i32_le(data + offset), static_cast<std::int32_t>(0LL));
    offset += 4;

    wire::require("SecurityDefinitionMessage", offset + 12, length);
    isin_number_ = wire::read_text(data + offset, 12, '\0');
    offset += 12;

    wire::require("SecurityDefinitionMessage", offset + 6, length);
    asset_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    wire::require("SecurityDefinitionMessage", offset + 6, length);
    cfi_code_ = wire::read_text(data + offset, 6, '\0');
    offset += 6;

    offset += maturity_month_year_.decode(data + offset, length - offset);

    offset += contract_settl_month_.decode(data + offset, length - offset);

    wire::require("SecurityDefinitionMessage", offset + 3, length);
    currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("SecurityDefinitionMessage", offset + 3, length);
    strike_currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("SecurityDefinitionMessage", offset + 3, length);
    settl_currency_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("SecurityDefinitionMessage", offset + 3, length);
    security_strategy_type_ = wire::read_text(data + offset, 3, '\0');
    offset += 3;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    lot_type_ = wire::nullable_enum<LotType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    tick_size_denominator_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    product_ = static_cast<Product>(wire::read_u8(data + offset));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    exercise_style_ = wire::nullable_enum<ExerciseStyle>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    put_or_call_ = wire::nullable_enum<PutOrCall>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    price_type_optional_ = wire::nullable_enum<PriceTypeOptional>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    market_segment_id_ = wire::nullable(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    governance_indicator_ = wire::nullable_enum<GovernanceIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    security_match_type_ = wire::nullable_enum<SecurityMatchType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    last_fragment_ = wire::nullable_enum<LastFragment>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    multi_leg_model_ = wire::nullable_enum<MultiLegModel>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    multi_leg_price_method_ = wire::nullable_enum<MultiLegPriceMethod>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 8, length);
    min_cross_qty_ = wire::nullable(wire::read_i64_le(data + offset), static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    implied_market_indicator_ = wire::nullable_enum<ImpliedMarketIndicator>(wire::read_u8(data + offset), static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::require("SecurityDefinitionMessage", offset + 1, length);
    opt_payout_type_ = wire::nullable_enum<OptPayoutType>(wire::read_u8(data + offset), static_cast<std::uint8_t>(0ULL));
    offset += 1;

    offset += underlyings_groups_.decode(data + offset, length - offset);

    offset += legs_groups_.decode(data + offset, length - offset);

    offset += instr_attribs_groups_.decode(data + offset, length - offset);

    offset += security_desc_.decode(data + offset, length - offset);

    return offset;
}

std::size_t SecurityDefinitionMessage::encode(std::byte* data, std::size_t capacity) const {
    std::size_t offset = 0;
    wire::require_capacity("SecurityDefinitionMessage", encoded_size(), capacity);

    wire::write_u64_le(data + offset, static_cast<std::uint64_t>(security_id_));
    offset += 8;

    wire::write_text(data + offset, 4, '\0', security_exchange_);
    offset += 4;

    wire::write_char(data + offset, static_cast<char>(security_id_source_));
    offset += 1;

    wire::write_text(data + offset, 3, '\0', security_group_);
    offset += 3;

    wire::write_text(data + offset, 20, '\0', symbol_);
    offset += 20;

    wire::write_char(data + offset, static_cast<char>(security_update_action_));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(security_type_));
    offset += 1;

    wire::write_u16_le(data + offset, static_cast<std::uint16_t>(security_sub_type_));
    offset += 2;

    wire::write_u32_le(data + offset, static_cast<std::uint32_t>(tot_no_related_sym_));
    offset += 4;

    wire::write_i64_le(data + offset, min_price_increment_ ? static_cast<std::int64_t>(min_price_increment_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, strike_price_ ? static_cast<std::int64_t>(strike_price_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, contract_multiplier_ ? static_cast<std::int64_t>(contract_multiplier_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, price_divisor_ ? static_cast<std::int64_t>(price_divisor_->mantissa()) : static_cast<std::int64_t>(-9223372036854775807LL - 1));
    offset += 8;

    wire::write_i64_le(data + offset, security_validity_timestamp_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_u64_le(data + offset, no_shares_issued_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_u64_le(data + offset, clearing_house_id_.value_or(static_cast<std::uint64_t>(0ULL)));
    offset += 8;

    wire::write_i64_le(data + offset, min_order_qty_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_i64_le(data + offset, max_order_qty_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_i64_le(data + offset, min_lot_size_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_i64_le(data + offset, min_trade_vol_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_u32_le(data + offset, corporate_action_event_id_.value_or(static_cast<std::uint32_t>(0ULL)));
    offset += 4;

    wire::write_i32_le(data + offset, static_cast<std::int32_t>(issue_date_));
    offset += 4;

    wire::write_i32_le(data + offset, maturity_date_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    wire::write_text(data + offset, 2, '\0', country_of_issue_);
    offset += 2;

    wire::write_i32_le(data + offset, start_date_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    wire::write_i32_le(data + offset, end_date_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    wire::write_u16_le(data + offset, settl_type_.value_or(static_cast<std::uint16_t>(65535ULL)));
    offset += 2;

    wire::write_i32_le(data + offset, settl_date_local_mkt_date_32_optional_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    wire::write_i32_le(data + offset, dated_date_.value_or(static_cast<std::int32_t>(0LL)));
    offset += 4;

    wire::write_text(data + offset, 12, '\0', isin_number_);
    offset += 12;

    wire::write_text(data + offset, 6, '\0', asset_);
    offset += 6;

    wire::write_text(data + offset, 6, '\0', cfi_code_);
    offset += 6;

    offset += maturity_month_year_.encode(data + offset, capacity - offset);

    offset += contract_settl_month_.encode(data + offset, capacity - offset);

    wire::write_text(data + offset, 3, '\0', currency_);
    offset += 3;

    wire::write_text(data + offset, 3, '\0', strike_currency_);
    offset += 3;

    wire::write_text(data + offset, 3, '\0', settl_currency_);
    offset += 3;

    wire::write_text(data + offset, 3, '\0', security_strategy_type_);
    offset += 3;

    wire::write_u8(data + offset, lot_type_ ? static_cast<std::uint8_t>(*lot_type_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, tick_size_denominator_.value_or(static_cast<std::uint8_t>(255ULL)));
    offset += 1;

    wire::write_u8(data + offset, static_cast<std::uint8_t>(product_));
    offset += 1;

    wire::write_u8(data + offset, exercise_style_ ? static_cast<std::uint8_t>(*exercise_style_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, put_or_call_ ? static_cast<std::uint8_t>(*put_or_call_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, price_type_optional_ ? static_cast<std::uint8_t>(*price_type_optional_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    wire::write_u8(data + offset, market_segment_id_.value_or(static_cast<std::uint8_t>(0ULL)));
    offset += 1;

    wire::write_u8(data + offset, governance_indicator_ ? static_cast<std::uint8_t>(*governance_indicator_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, security_match_type_ ? static_cast<std::uint8_t>(*security_match_type_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, last_fragment_ ? static_cast<std::uint8_t>(*last_fragment_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, multi_leg_model_ ? static_cast<std::uint8_t>(*multi_leg_model_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, multi_leg_price_method_ ? static_cast<std::uint8_t>(*multi_leg_price_method_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_i64_le(data + offset, min_cross_qty_.value_or(static_cast<std::int64_t>(-9223372036854775807LL - 1)));
    offset += 8;

    wire::write_u8(data + offset, implied_market_indicator_ ? static_cast<std::uint8_t>(*implied_market_indicator_) : static_cast<std::uint8_t>(255ULL));
    offset += 1;

    wire::write_u8(data + offset, opt_payout_type_ ? static_cast<std::uint8_t>(*opt_payout_type_) : static_cast<std::uint8_t>(0ULL));
    offset += 1;

    offset += underlyings_groups_.encode(data + offset, capacity - offset);

    offset += legs_groups_.encode(data + offset, capacity - offset);

    offset += instr_attribs_groups_.encode(data + offset, capacity - offset);

    offset += security_desc_.encode(data + offset, capacity - offset);

    return offset;
}

std::size_t SecurityDefinitionMessage::encoded_size() const {
    return 8 + 4 + 1 + 3 + 20 + 1 + 1 + 2 + 4 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 4 + 4 + 4 + 2 + 4 + 4 + 2 + 4 + 4 + 12 + 6 + 6 + maturity_month_year_.encoded_size() + contract_settl_month_.encoded_size() + 3 + 3 + 3 + 3 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 8 + 1 + 1 + underlyings_groups_.encoded_size() + legs_groups_.encoded_size() + instr_attribs_groups_.encoded_size() + security_desc_.encoded_size();
}

void SecurityDefinitionMessage::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

std::unique_ptr<Message> SecurityDefinitionMessage::clone() const {
    return std::make_unique<SecurityDefinitionMessage>(*this);
}

void SecurityDefinitionMessage::print(std::ostream& out) const {
    out << "SecurityDefinitionMessage{";
    out << "security_id=";
    out << security_id_;
    out << ", security_exchange=";
    print::text(out, security_exchange_);
    out << ", security_id_source=";
    out << security_id_source_;
    out << ", security_group=";
    print::text(out, security_group_);
    out << ", symbol=";
    print::text(out, symbol_);
    out << ", security_update_action=";
    out << security_update_action_;
    out << ", security_type=";
    out << security_type_;
    out << ", security_sub_type=";
    out << security_sub_type_;
    out << ", tot_no_related_sym=";
    out << tot_no_related_sym_;
    out << ", min_price_increment=";
    print::optional(out, min_price_increment_);
    out << ", strike_price=";
    print::optional(out, strike_price_);
    out << ", contract_multiplier=";
    print::optional(out, contract_multiplier_);
    out << ", price_divisor=";
    print::optional(out, price_divisor_);
    out << ", security_validity_timestamp=";
    print::optional(out, security_validity_timestamp_);
    out << ", no_shares_issued=";
    print::optional(out, no_shares_issued_);
    out << ", clearing_house_id=";
    print::optional(out, clearing_house_id_);
    out << ", min_order_qty=";
    print::optional(out, min_order_qty_);
    out << ", max_order_qty=";
    print::optional(out, max_order_qty_);
    out << ", min_lot_size=";
    print::optional(out, min_lot_size_);
    out << ", min_trade_vol=";
    print::optional(out, min_trade_vol_);
    out << ", corporate_action_event_id=";
    print::optional(out, corporate_action_event_id_);
    out << ", issue_date=";
    out << issue_date_;
    out << ", maturity_date=";
    print::optional(out, maturity_date_);
    out << ", country_of_issue=";
    print::text(out, country_of_issue_);
    out << ", start_date=";
    print::optional(out, start_date_);
    out << ", end_date=";
    print::optional(out, end_date_);
    out << ", settl_type=";
    print::optional(out, settl_type_);
    out << ", settl_date_local_mkt_date_32_optional=";
    print::optional(out, settl_date_local_mkt_date_32_optional_);
    out << ", dated_date=";
    print::optional(out, dated_date_);
    out << ", isin_number=";
    print::text(out, isin_number_);
    out << ", asset=";
    print::text(out, asset_);
    out << ", cfi_code=";
    print::text(out, cfi_code_);
    out << ", maturity_month_year=";
    maturity_month_year_.print(out);
    out << ", contract_settl_month=";
    contract_settl_month_.print(out);
    out << ", currency=";
    print::text(out, currency_);
    out << ", strike_currency=";
    print::text(out, strike_currency_);
    out << ", settl_currency=";
    print::text(out, settl_currency_);
    out << ", security_strategy_type=";
    print::text(out, security_strategy_type_);
    out << ", lot_type=";
    print::optional(out, lot_type_);
    out << ", tick_size_denominator=";
    print::optional(out, tick_size_denominator_);
    out << ", product=";
    out << product_;
    out << ", exercise_style=";
    print::optional(out, exercise_style_);
    out << ", put_or_call=";
    print::optional(out, put_or_call_);
    out << ", price_type_optional=";
    print::optional(out, price_type_optional_);
    out << ", market_segment_id=";
    print::optional(out, market_segment_id_);
    out << ", governance_indicator=";
    print::optional(out, governance_indicator_);
    out << ", security_match_type=";
    print::optional(out, security_match_type_);
    out << ", last_fragment=";
    print::optional(out, last_fragment_);
    out << ", multi_leg_model=";
    print::optional(out, multi_leg_model_);
    out << ", multi_leg_price_method=";
    print::optional(out, multi_leg_price_method_);
    out << ", min_cross_qty=";
    print::optional(out, min_cross_qty_);
    out << ", implied_market_indicator=";
    print::optional(out, implied_market_indicator_);
    out << ", opt_payout_type=";
    print::optional(out, opt_payout_type_);
    out << ", underlyings_groups=";
    underlyings_groups_.print(out);
    out << ", legs_groups=";
    legs_groups_.print(out);
    out << ", instr_attribs_groups=";
    instr_attribs_groups_.print(out);
    out << ", security_desc=";
    security_desc_.print(out);
    out << '}';
}

bool SecurityDefinitionMessage::equals(const Message& other) const {
    const auto* that = dynamic_cast<const SecurityDefinitionMessage*>(&other);
    return that != nullptr && *this == *that;
}

bool SecurityDefinitionMessage::operator==(const SecurityDefinitionMessage& other) const {
    return security_id_ == other.security_id_
        && security_exchange_ == other.security_exchange_
        && security_id_source_ == other.security_id_source_
        && security_group_ == other.security_group_
        && symbol_ == other.symbol_
        && security_update_action_ == other.security_update_action_
        && security_type_ == other.security_type_
        && security_sub_type_ == other.security_sub_type_
        && tot_no_related_sym_ == other.tot_no_related_sym_
        && min_price_increment_ == other.min_price_increment_
        && strike_price_ == other.strike_price_
        && contract_multiplier_ == other.contract_multiplier_
        && price_divisor_ == other.price_divisor_
        && security_validity_timestamp_ == other.security_validity_timestamp_
        && no_shares_issued_ == other.no_shares_issued_
        && clearing_house_id_ == other.clearing_house_id_
        && min_order_qty_ == other.min_order_qty_
        && max_order_qty_ == other.max_order_qty_
        && min_lot_size_ == other.min_lot_size_
        && min_trade_vol_ == other.min_trade_vol_
        && corporate_action_event_id_ == other.corporate_action_event_id_
        && issue_date_ == other.issue_date_
        && maturity_date_ == other.maturity_date_
        && country_of_issue_ == other.country_of_issue_
        && start_date_ == other.start_date_
        && end_date_ == other.end_date_
        && settl_type_ == other.settl_type_
        && settl_date_local_mkt_date_32_optional_ == other.settl_date_local_mkt_date_32_optional_
        && dated_date_ == other.dated_date_
        && isin_number_ == other.isin_number_
        && asset_ == other.asset_
        && cfi_code_ == other.cfi_code_
        && maturity_month_year_ == other.maturity_month_year_
        && contract_settl_month_ == other.contract_settl_month_
        && currency_ == other.currency_
        && strike_currency_ == other.strike_currency_
        && settl_currency_ == other.settl_currency_
        && security_strategy_type_ == other.security_strategy_type_
        && lot_type_ == other.lot_type_
        && tick_size_denominator_ == other.tick_size_denominator_
        && product_ == other.product_
        && exercise_style_ == other.exercise_style_
        && put_or_call_ == other.put_or_call_
        && price_type_optional_ == other.price_type_optional_
        && market_segment_id_ == other.market_segment_id_
        && governance_indicator_ == other.governance_indicator_
        && security_match_type_ == other.security_match_type_
        && last_fragment_ == other.last_fragment_
        && multi_leg_model_ == other.multi_leg_model_
        && multi_leg_price_method_ == other.multi_leg_price_method_
        && min_cross_qty_ == other.min_cross_qty_
        && implied_market_indicator_ == other.implied_market_indicator_
        && opt_payout_type_ == other.opt_payout_type_
        && underlyings_groups_ == other.underlyings_groups_
        && legs_groups_ == other.legs_groups_
        && instr_attribs_groups_ == other.instr_attribs_groups_
        && security_desc_ == other.security_desc_;
}

bool SecurityDefinitionMessage::operator!=(const SecurityDefinitionMessage& other) const {
    return !(*this == other);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
