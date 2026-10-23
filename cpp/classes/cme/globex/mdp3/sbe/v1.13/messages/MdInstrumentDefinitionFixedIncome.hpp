#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../bitfields/MatchEventIndicator.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdSecurityTradingStatus.hpp"
#include "../enums/SecurityAltIdSource.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../messages/MktdataPayload.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/LotTypeRulesGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class MktdataPayloadVisitor;

// MDInstrumentDefinitionFixedIncome
class MdInstrumentDefinitionFixedIncome : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::MdInstrumentDefinitionFixedIncome;

    MdInstrumentDefinitionFixedIncome() = default;
    MdInstrumentDefinitionFixedIncome(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const std::string& currency, const std::string& settl_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, std::optional<Decimal> min_price_increment_optional_ex, Decimal display_factor, std::optional<std::uint8_t> main_fraction, std::optional<std::uint8_t> sub_fraction, std::optional<std::uint8_t> price_display_format, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> trading_reference_price, std::optional<std::uint16_t> trading_reference_date, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::optional<Decimal> min_price_increment_amount, std::optional<std::uint16_t> issue_date, std::optional<std::uint16_t> dated_date, std::optional<std::uint16_t> maturity_date, std::optional<Decimal> coupon_rate, std::optional<Decimal> par_value, const std::string& coupon_frequency_unit, std::optional<std::uint16_t> coupon_frequency_period, const std::string& coupon_day_count, const std::string& country_of_issue, const std::string& issuer, const std::string& financial_instrument_full_name, const std::string& security_alt_id, std::optional<SecurityAltIdSource> security_alt_id_source, const std::string& price_quote_method, const std::string& party_role_clearing_org, char user_defined_instrument, const std::string& risk_set, const std::string& market_set, std::optional<std::uint64_t> instrument_guid, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups);

    // Match Event Indicator: MatchEventIndicator bit set
    const MatchEventIndicator& match_event_indicator() const;
    MatchEventIndicator& match_event_indicator();
    void set_match_event_indicator(const MatchEventIndicator& value);

    // Tot Num Reports Optional: Total number of instruments in the Replay loop. Used on Replay
    // Feed only
    std::optional<std::uint32_t> tot_num_reports_optional() const;
    void set_tot_num_reports_optional(std::optional<std::uint32_t> value);

    // Security Update Action: Last Security update action on Incremental feed, 'D' or 'M' is
    // used when a mid-week deletion or modification (i.e. extension) occurs
    SecurityUpdateAction security_update_action() const;
    void set_security_update_action(SecurityUpdateAction value);

    // Last Update Time: UTC Date and time of last Security Definition add, update or delete on
    // a given Market Data channel
    std::chrono::nanoseconds last_update_time() const;
    void set_last_update_time(std::chrono::nanoseconds value);

    // Md Security Trading Status: Identifies the current trading state of the instrument
    std::optional<MdSecurityTradingStatus> md_security_trading_status() const;
    void set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value);

    // Appl Id: The channel ID as defined in the XML Configuration file
    std::int16_t appl_id() const;
    void set_appl_id(std::int16_t value);

    // Market Segment Id: Identifies the market segment, populated for all CME Globex
    // instruments
    std::uint8_t market_segment_id() const;
    void set_market_segment_id(std::uint8_t value);

    // Underlying Product: Product complex
    std::uint8_t underlying_product() const;
    void set_underlying_product(std::uint8_t value);

    // Security Exchange: Exchange used to identify a security
    const std::string& security_exchange() const;
    std::string& security_exchange();
    void set_security_exchange(const std::string& value);

    // Security Group: Security Group
    const std::string& security_group() const;
    std::string& security_group();
    void set_security_group(const std::string& value);

    // Asset: Product Code within Security Group specified
    const std::string& asset() const;
    std::string& asset();
    void set_asset(const std::string& value);

    // Symbol: Instrument Name or Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Security Id: Security ID
    std::int32_t security_id() const;
    void set_security_id(std::int32_t value);

    // Security Type: Security Type
    const std::string& security_type() const;
    std::string& security_type();
    void set_security_type(const std::string& value);

    // Cfi Code: ISO standard instrument categorization code
    const std::string& cfi_code() const;
    std::string& cfi_code();
    void set_cfi_code(const std::string& value);

    // Currency: Identifies currency used for price
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Settl Currency: Identifies currency used for settlement, if different from trading
    // currency
    const std::string& settl_currency() const;
    std::string& settl_currency();
    void set_settl_currency(const std::string& value);

    // Match Algorithm: Matching algorithm
    char match_algorithm() const;
    void set_match_algorithm(char value);

    // Min Trade Vol: The minimum trading volume for a security
    std::uint32_t min_trade_vol() const;
    void set_min_trade_vol(std::uint32_t value);

    // Max Trade Vol: The maximum trading volume for a security
    std::uint32_t max_trade_vol() const;
    void set_max_trade_vol(std::uint32_t value);

    // Min Price Increment Optional Ex: Minimum constant tick for the instrument
    std::optional<Decimal> min_price_increment_optional_ex() const;
    void set_min_price_increment_optional_ex(std::optional<Decimal> value);

    // Display Factor: Contains the multiplier to convert the CME Globex display price to the
    // conventional price
    Decimal display_factor() const;
    void set_display_factor(Decimal value);

    // Main Fraction: Price Denominator of Main Fraction
    std::optional<std::uint8_t> main_fraction() const;
    void set_main_fraction(std::optional<std::uint8_t> value);

    // Sub Fraction: Price Denominator of Sub Fraction
    std::optional<std::uint8_t> sub_fraction() const;
    void set_sub_fraction(std::optional<std::uint8_t> value);

    // Price Display Format: Number of decimals in fractional display price
    std::optional<std::uint8_t> price_display_format() const;
    void set_price_display_format(std::optional<std::uint8_t> value);

    // Unit Of Measure: Unit of measure for the products' original contract size. This will be
    // populated for all products listed on CME Globex
    const std::string& unit_of_measure() const;
    std::string& unit_of_measure();
    void set_unit_of_measure(const std::string& value);

    // Unit Of Measure Qty: This field contains the contract size for each instrument. Used in
    // combination with tag 996-UnitofMeasure
    std::optional<Decimal> unit_of_measure_qty() const;
    void set_unit_of_measure_qty(std::optional<Decimal> value);

    // Trading Reference Price: Reference price for prelisted instruments or the last
    // calculated Settlement whether it be Theoretical, Preliminary or a Final Settle of the
    // session.
    std::optional<Decimal> trading_reference_price() const;
    void set_trading_reference_price(std::optional<Decimal> value);

    // Trading Reference Date: Indicates session date corresponding to the settlement price in
    // tag 1150-TradingReferencePrice
    std::optional<std::uint16_t> trading_reference_date() const;
    void set_trading_reference_date(std::optional<std::uint16_t> value);

    // High Limit Price: Upper price threshold for the instrument
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: Lower price threshold for the instrument
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: Differential value for price banding
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // Min Price Increment Amount: Monetary value equivalent to the minimum price fluctuation
    std::optional<Decimal> min_price_increment_amount() const;
    void set_min_price_increment_amount(std::optional<Decimal> value);

    // Issue Date: Issue Date
    std::optional<std::uint16_t> issue_date() const;
    void set_issue_date(std::optional<std::uint16_t> value);

    // Dated Date: Dated Date
    std::optional<std::uint16_t> dated_date() const;
    void set_dated_date(std::optional<std::uint16_t> value);

    // Maturity Date: Maturity Date
    std::optional<std::uint16_t> maturity_date() const;
    void set_maturity_date(std::optional<std::uint16_t> value);

    // Coupon Rate: The rate of interest that, when multiplied by the principal, par value, or
    // face value of a bond, provides the currency amount of the periodic interest payment
    std::optional<Decimal> coupon_rate() const;
    void set_coupon_rate(std::optional<Decimal> value);

    // Par Value: Par value
    std::optional<Decimal> par_value() const;
    void set_par_value(std::optional<Decimal> value);

    // Coupon Frequency Unit: Time unit associated with the frequency of the bond's coupon
    // payment
    const std::string& coupon_frequency_unit() const;
    std::string& coupon_frequency_unit();
    void set_coupon_frequency_unit(const std::string& value);

    // Coupon Frequency Period: Time unit multiplier for the frequency of the bond's coupon
    // payment
    std::optional<std::uint16_t> coupon_frequency_period() const;
    void set_coupon_frequency_period(std::optional<std::uint16_t> value);

    // Coupon Day Count: The day count convention used in interest calculations for a bond or
    // an interest bearing security
    const std::string& coupon_day_count() const;
    std::string& coupon_day_count();
    void set_coupon_day_count(const std::string& value);

    // Country Of Issue: Country of Origin, ISO alpha-2 country code
    const std::string& country_of_issue() const;
    std::string& country_of_issue();
    void set_country_of_issue(const std::string& value);

    // Issuer: Name of security issuer or the Legal Entity Identifier (LEI - the International
    // ISO standard 17442)
    const std::string& issuer() const;
    std::string& issuer();
    void set_issuer(const std::string& value);

    // Financial Instrument Full Name: Long name of the instrument
    const std::string& financial_instrument_full_name() const;
    std::string& financial_instrument_full_name();
    void set_financial_instrument_full_name(const std::string& value);

    // Security Alt Id: Expanded instrument description. Will contain either ISIN or CUSIP
    const std::string& security_alt_id() const;
    std::string& security_alt_id();
    void set_security_alt_id(const std::string& value);

    // Security Alt Id Source: Identifies class or source of the SecurityAltID (455) value
    std::optional<SecurityAltIdSource> security_alt_id_source() const;
    void set_security_alt_id_source(std::optional<SecurityAltIdSource> value);

    // Price Quote Method: Price quotation method
    const std::string& price_quote_method() const;
    std::string& price_quote_method();
    void set_price_quote_method(const std::string& value);

    // Party Role Clearing Org: Clearing organization
    const std::string& party_role_clearing_org() const;
    std::string& party_role_clearing_org();
    void set_party_role_clearing_org(const std::string& value);

    // User Defined Instrument: User-defined instruments flag
    char user_defined_instrument() const;
    void set_user_defined_instrument(char value);

    // Risk Set: Risk Set identifies the list of instruments sharing credit limits set up
    const std::string& risk_set() const;
    std::string& risk_set();
    void set_risk_set(const std::string& value);

    // Market Set: Market Set defines the bilateral relationship and Self Match Prevention
    // configuration for eligible markets
    const std::string& market_set() const;
    std::string& market_set();
    void set_market_set(const std::string& value);

    // Instrument Guid: External unique instrument ID
    std::optional<std::uint64_t> instrument_guid() const;
    void set_instrument_guid(std::optional<std::uint64_t> value);

    // Events Groups: NoEvents Block
    const EventsGroups& events_groups() const;
    EventsGroups& events_groups();
    void set_events_groups(const EventsGroups& value);

    // Feed Types Groups: NoMDFeedTypes Block
    const FeedTypesGroups& feed_types_groups() const;
    FeedTypesGroups& feed_types_groups();
    void set_feed_types_groups(const FeedTypesGroups& value);

    // Inst Attrib Groups: NoInstAttrib Block
    const InstAttribGroups& inst_attrib_groups() const;
    InstAttribGroups& inst_attrib_groups();
    void set_inst_attrib_groups(const InstAttribGroups& value);

    // Lot Type Rules Groups: NoLotTypeRules Block
    const LotTypeRulesGroups& lot_type_rules_groups() const;
    LotTypeRulesGroups& lot_type_rules_groups();
    void set_lot_type_rules_groups(const LotTypeRulesGroups& value);

    // MktdataPayload
    MktdataPayloadCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(MktdataPayloadVisitor& visitor) const override;
    std::unique_ptr<MktdataPayload> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const MktdataPayload& other) const override;

    bool operator==(const MdInstrumentDefinitionFixedIncome& other) const;
    bool operator!=(const MdInstrumentDefinitionFixedIncome& other) const;

  private:
    MatchEventIndicator match_event_indicator_{};
    std::optional<std::uint32_t> tot_num_reports_optional_{};
    SecurityUpdateAction security_update_action_{};
    std::chrono::nanoseconds last_update_time_{};
    std::optional<MdSecurityTradingStatus> md_security_trading_status_{};
    std::int16_t appl_id_{};
    std::uint8_t market_segment_id_{};
    std::uint8_t underlying_product_{};
    std::string security_exchange_{};
    std::string security_group_{};
    std::string asset_{};
    std::string symbol_{};
    std::int32_t security_id_{};
    std::string security_type_{};
    std::string cfi_code_{};
    std::string currency_{};
    std::string settl_currency_{};
    char match_algorithm_{};
    std::uint32_t min_trade_vol_{};
    std::uint32_t max_trade_vol_{};
    std::optional<Decimal> min_price_increment_optional_ex_{};
    Decimal display_factor_{ 0, -9 };
    std::optional<std::uint8_t> main_fraction_{};
    std::optional<std::uint8_t> sub_fraction_{};
    std::optional<std::uint8_t> price_display_format_{};
    std::string unit_of_measure_{};
    std::optional<Decimal> unit_of_measure_qty_{};
    std::optional<Decimal> trading_reference_price_{};
    std::optional<std::uint16_t> trading_reference_date_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    std::optional<Decimal> min_price_increment_amount_{};
    std::optional<std::uint16_t> issue_date_{};
    std::optional<std::uint16_t> dated_date_{};
    std::optional<std::uint16_t> maturity_date_{};
    std::optional<Decimal> coupon_rate_{};
    std::optional<Decimal> par_value_{};
    std::string coupon_frequency_unit_{};
    std::optional<std::uint16_t> coupon_frequency_period_{};
    std::string coupon_day_count_{};
    std::string country_of_issue_{};
    std::string issuer_{};
    std::string financial_instrument_full_name_{};
    std::string security_alt_id_{};
    std::optional<SecurityAltIdSource> security_alt_id_source_{};
    std::string price_quote_method_{};
    std::string party_role_clearing_org_{};
    char user_defined_instrument_{};
    std::string risk_set_{};
    std::string market_set_{};
    std::optional<std::uint64_t> instrument_guid_{};
    EventsGroups events_groups_{};
    FeedTypesGroups feed_types_groups_{};
    InstAttribGroups inst_attrib_groups_{};
    LotTypeRulesGroups lot_type_rules_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
