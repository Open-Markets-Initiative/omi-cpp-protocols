#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ExerciseStyle.hpp"
#include "../enums/GovernanceIndicator.hpp"
#include "../enums/LastFragment.hpp"
#include "../enums/LotType.hpp"
#include "../enums/MultiLegModel.hpp"
#include "../enums/MultiLegPriceMethod.hpp"
#include "../enums/PriceType.hpp"
#include "../enums/Product.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/SecurityIdSource.hpp"
#include "../enums/SecurityMatchType.hpp"
#include "../enums/SecurityType.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../messages/Message.hpp"
#include "../structs/ContractSettlMonth.hpp"
#include "../structs/InstrAttribsGroups.hpp"
#include "../structs/LegsGroups.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../structs/SecurityDesc.hpp"
#include "../structs/UnderlyingsGroups.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

class Visitor;

// SecurityDefinition_12Message
class SecurityDefinitionMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = TemplateId::SecurityDefinitionMessage;

    SecurityDefinitionMessage() = default;
    SecurityDefinitionMessage(std::uint64_t security_id, const std::string& security_exchange, SecurityIdSource security_id_source, const std::string& security_group, const std::string& symbol, SecurityUpdateAction security_update_action, SecurityType security_type, std::uint16_t security_sub_type, std::uint32_t tot_no_related_sym, std::optional<Decimal> min_price_increment_optional, std::optional<Decimal> strike_price, std::optional<Decimal> contract_multiplier, std::optional<Decimal> price_divisor, std::optional<std::int64_t> security_validity_timestamp, std::optional<std::uint64_t> no_shares_issued, std::optional<std::uint64_t> clearing_house_id, std::optional<std::int64_t> min_order_qty, std::optional<std::int64_t> max_order_qty, std::optional<std::int64_t> min_lot_size, std::optional<std::int64_t> min_trade_vol, std::optional<std::uint32_t> corporate_action_event_id, std::int32_t issue_date, std::optional<std::int32_t> maturity_date, const std::string& country_of_issue, std::optional<std::int32_t> start_date, std::optional<std::int32_t> end_date, std::optional<std::uint16_t> settl_type, std::optional<std::int32_t> settl_date, std::optional<std::int32_t> dated_date, const std::string& isin_number, const std::string& asset, const std::string& cfi_code, const MaturityMonthYear& maturity_month_year, const ContractSettlMonth& contract_settl_month, const std::string& currency, const std::string& strike_currency, const std::string& settl_currency, const std::string& security_strategy_type, std::optional<LotType> lot_type, std::optional<std::uint8_t> tick_size_denominator, Product product, std::optional<ExerciseStyle> exercise_style, std::optional<PutOrCall> put_or_call, std::optional<PriceType> price_type, std::optional<std::uint8_t> market_segment_id, std::optional<GovernanceIndicator> governance_indicator, std::optional<SecurityMatchType> security_match_type, std::optional<LastFragment> last_fragment, std::optional<MultiLegModel> multi_leg_model, std::optional<MultiLegPriceMethod> multi_leg_price_method, std::optional<std::int64_t> min_cross_qty, const UnderlyingsGroups& underlyings_groups, const LegsGroups& legs_groups, const InstrAttribsGroups& instr_attribs_groups, const SecurityDesc& security_desc);

    // Security Id: securityID
    std::uint64_t security_id() const;
    void set_security_id(std::uint64_t value);

    // Security Exchange: securityExchange
    const std::string& security_exchange() const;
    std::string& security_exchange();
    void set_security_exchange(const std::string& value);

    // Security Id Source: securityIDSource
    SecurityIdSource security_id_source() const;
    void set_security_id_source(SecurityIdSource value);

    // Security Group: securityGroup
    const std::string& security_group() const;
    std::string& security_group();
    void set_security_group(const std::string& value);

    // Symbol: symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Security Update Action: securityUpdateAction
    SecurityUpdateAction security_update_action() const;
    void set_security_update_action(SecurityUpdateAction value);

    // Security Type: securityType
    SecurityType security_type() const;
    void set_security_type(SecurityType value);

    // Security Sub Type: securitySubType
    std::uint16_t security_sub_type() const;
    void set_security_sub_type(std::uint16_t value);

    // Tot No Related Sym: totNoRelatedSym
    std::uint32_t tot_no_related_sym() const;
    void set_tot_no_related_sym(std::uint32_t value);

    // Min Price Increment Optional: minPriceIncrement
    std::optional<Decimal> min_price_increment_optional() const;
    void set_min_price_increment_optional(std::optional<Decimal> value);

    // Strike Price: strikePrice
    std::optional<Decimal> strike_price() const;
    void set_strike_price(std::optional<Decimal> value);

    // Contract Multiplier: contractMultiplier
    std::optional<Decimal> contract_multiplier() const;
    void set_contract_multiplier(std::optional<Decimal> value);

    // Price Divisor: priceDivisor
    std::optional<Decimal> price_divisor() const;
    void set_price_divisor(std::optional<Decimal> value);

    // Security Validity Timestamp: securityValidityTimestamp
    std::optional<std::int64_t> security_validity_timestamp() const;
    void set_security_validity_timestamp(std::optional<std::int64_t> value);

    // No Shares Issued: noSharesIssued
    std::optional<std::uint64_t> no_shares_issued() const;
    void set_no_shares_issued(std::optional<std::uint64_t> value);

    // Clearing House Id: clearingHouseID
    std::optional<std::uint64_t> clearing_house_id() const;
    void set_clearing_house_id(std::optional<std::uint64_t> value);

    // Min Order Qty: minOrderQty
    std::optional<std::int64_t> min_order_qty() const;
    void set_min_order_qty(std::optional<std::int64_t> value);

    // Max Order Qty: maxOrderQty
    std::optional<std::int64_t> max_order_qty() const;
    void set_max_order_qty(std::optional<std::int64_t> value);

    // Min Lot Size: minLotSize
    std::optional<std::int64_t> min_lot_size() const;
    void set_min_lot_size(std::optional<std::int64_t> value);

    // Min Trade Vol: minTradeVol
    std::optional<std::int64_t> min_trade_vol() const;
    void set_min_trade_vol(std::optional<std::int64_t> value);

    // Corporate Action Event Id: corporateActionEventId
    std::optional<std::uint32_t> corporate_action_event_id() const;
    void set_corporate_action_event_id(std::optional<std::uint32_t> value);

    // Issue Date: issueDate
    std::int32_t issue_date() const;
    void set_issue_date(std::int32_t value);

    // Maturity Date: maturityDate
    std::optional<std::int32_t> maturity_date() const;
    void set_maturity_date(std::optional<std::int32_t> value);

    // Country Of Issue: countryOfIssue
    const std::string& country_of_issue() const;
    std::string& country_of_issue();
    void set_country_of_issue(const std::string& value);

    // Start Date: startDate
    std::optional<std::int32_t> start_date() const;
    void set_start_date(std::optional<std::int32_t> value);

    // End Date: endDate
    std::optional<std::int32_t> end_date() const;
    void set_end_date(std::optional<std::int32_t> value);

    // Settl Type: settlType
    std::optional<std::uint16_t> settl_type() const;
    void set_settl_type(std::optional<std::uint16_t> value);

    // Settl Date: settlDate
    std::optional<std::int32_t> settl_date() const;
    void set_settl_date(std::optional<std::int32_t> value);

    // Dated Date: datedDate
    std::optional<std::int32_t> dated_date() const;
    void set_dated_date(std::optional<std::int32_t> value);

    // Isin Number: isinNumber
    const std::string& isin_number() const;
    std::string& isin_number();
    void set_isin_number(const std::string& value);

    // Asset: asset
    const std::string& asset() const;
    std::string& asset();
    void set_asset(const std::string& value);

    // Cfi Code: cfiCode
    const std::string& cfi_code() const;
    std::string& cfi_code();
    void set_cfi_code(const std::string& value);

    // Maturity Month Year: SecurityDefinition_4Message
    const MaturityMonthYear& maturity_month_year() const;
    MaturityMonthYear& maturity_month_year();
    void set_maturity_month_year(const MaturityMonthYear& value);

    // Contract Settl Month: SecurityDefinition_4Message
    const ContractSettlMonth& contract_settl_month() const;
    ContractSettlMonth& contract_settl_month();
    void set_contract_settl_month(const ContractSettlMonth& value);

    // Currency: currency
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Strike Currency: strikeCurrency
    const std::string& strike_currency() const;
    std::string& strike_currency();
    void set_strike_currency(const std::string& value);

    // Settl Currency: settlCurrency
    const std::string& settl_currency() const;
    std::string& settl_currency();
    void set_settl_currency(const std::string& value);

    // Security Strategy Type: securityStrategyType
    const std::string& security_strategy_type() const;
    std::string& security_strategy_type();
    void set_security_strategy_type(const std::string& value);

    // Lot Type: lotType
    std::optional<LotType> lot_type() const;
    void set_lot_type(std::optional<LotType> value);

    // Tick Size Denominator: tickSizeDenominator
    std::optional<std::uint8_t> tick_size_denominator() const;
    void set_tick_size_denominator(std::optional<std::uint8_t> value);

    // Product: product
    Product product() const;
    void set_product(Product value);

    // Exercise Style: exerciseStyle
    std::optional<ExerciseStyle> exercise_style() const;
    void set_exercise_style(std::optional<ExerciseStyle> value);

    // Put Or Call: putOrCall
    std::optional<PutOrCall> put_or_call() const;
    void set_put_or_call(std::optional<PutOrCall> value);

    // Price Type: priceType
    std::optional<PriceType> price_type() const;
    void set_price_type(std::optional<PriceType> value);

    // Market Segment Id: marketSegmentID
    std::optional<std::uint8_t> market_segment_id() const;
    void set_market_segment_id(std::optional<std::uint8_t> value);

    // Governance Indicator: governanceIndicator
    std::optional<GovernanceIndicator> governance_indicator() const;
    void set_governance_indicator(std::optional<GovernanceIndicator> value);

    // Security Match Type: securityMatchType
    std::optional<SecurityMatchType> security_match_type() const;
    void set_security_match_type(std::optional<SecurityMatchType> value);

    // Last Fragment: lastFragment
    std::optional<LastFragment> last_fragment() const;
    void set_last_fragment(std::optional<LastFragment> value);

    // Multi Leg Model: multiLegModel
    std::optional<MultiLegModel> multi_leg_model() const;
    void set_multi_leg_model(std::optional<MultiLegModel> value);

    // Multi Leg Price Method: multiLegPriceMethod
    std::optional<MultiLegPriceMethod> multi_leg_price_method() const;
    void set_multi_leg_price_method(std::optional<MultiLegPriceMethod> value);

    // Min Cross Qty: minCrossQty
    std::optional<std::int64_t> min_cross_qty() const;
    void set_min_cross_qty(std::optional<std::int64_t> value);

    // Underlyings Groups: noUnderlyings Block
    const UnderlyingsGroups& underlyings_groups() const;
    UnderlyingsGroups& underlyings_groups();
    void set_underlyings_groups(const UnderlyingsGroups& value);

    // Legs Groups: noLegs Block
    const LegsGroups& legs_groups() const;
    LegsGroups& legs_groups();
    void set_legs_groups(const LegsGroups& value);

    // Instr Attribs Groups: noInstrAttribs Block
    const InstrAttribsGroups& instr_attribs_groups() const;
    InstrAttribsGroups& instr_attribs_groups();
    void set_instr_attribs_groups(const InstrAttribsGroups& value);

    // Security Desc: securityDesc data struct
    const SecurityDesc& security_desc() const;
    SecurityDesc& security_desc();
    void set_security_desc(const SecurityDesc& value);

    // Message
    MessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(Visitor& visitor) const override;
    std::unique_ptr<Message> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Message& other) const override;

    bool operator==(const SecurityDefinitionMessage& other) const;
    bool operator!=(const SecurityDefinitionMessage& other) const;

  private:
    std::uint64_t security_id_{};
    std::string security_exchange_{};
    SecurityIdSource security_id_source_{};
    std::string security_group_{};
    std::string symbol_{};
    SecurityUpdateAction security_update_action_{};
    SecurityType security_type_{};
    std::uint16_t security_sub_type_{};
    std::uint32_t tot_no_related_sym_{};
    std::optional<Decimal> min_price_increment_optional_{};
    std::optional<Decimal> strike_price_{};
    std::optional<Decimal> contract_multiplier_{};
    std::optional<Decimal> price_divisor_{};
    std::optional<std::int64_t> security_validity_timestamp_{};
    std::optional<std::uint64_t> no_shares_issued_{};
    std::optional<std::uint64_t> clearing_house_id_{};
    std::optional<std::int64_t> min_order_qty_{};
    std::optional<std::int64_t> max_order_qty_{};
    std::optional<std::int64_t> min_lot_size_{};
    std::optional<std::int64_t> min_trade_vol_{};
    std::optional<std::uint32_t> corporate_action_event_id_{};
    std::int32_t issue_date_{};
    std::optional<std::int32_t> maturity_date_{};
    std::string country_of_issue_{};
    std::optional<std::int32_t> start_date_{};
    std::optional<std::int32_t> end_date_{};
    std::optional<std::uint16_t> settl_type_{};
    std::optional<std::int32_t> settl_date_{};
    std::optional<std::int32_t> dated_date_{};
    std::string isin_number_{};
    std::string asset_{};
    std::string cfi_code_{};
    MaturityMonthYear maturity_month_year_{};
    ContractSettlMonth contract_settl_month_{};
    std::string currency_{};
    std::string strike_currency_{};
    std::string settl_currency_{};
    std::string security_strategy_type_{};
    std::optional<LotType> lot_type_{};
    std::optional<std::uint8_t> tick_size_denominator_{};
    Product product_{};
    std::optional<ExerciseStyle> exercise_style_{};
    std::optional<PutOrCall> put_or_call_{};
    std::optional<PriceType> price_type_{};
    std::optional<std::uint8_t> market_segment_id_{};
    std::optional<GovernanceIndicator> governance_indicator_{};
    std::optional<SecurityMatchType> security_match_type_{};
    std::optional<LastFragment> last_fragment_{};
    std::optional<MultiLegModel> multi_leg_model_{};
    std::optional<MultiLegPriceMethod> multi_leg_price_method_{};
    std::optional<std::int64_t> min_cross_qty_{};
    UnderlyingsGroups underlyings_groups_{};
    LegsGroups legs_groups_{};
    InstrAttribsGroups instr_attribs_groups_{};
    SecurityDesc security_desc_{};
};

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
