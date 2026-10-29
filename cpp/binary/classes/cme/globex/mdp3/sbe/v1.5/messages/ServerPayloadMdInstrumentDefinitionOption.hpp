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
#include "../bitfields/SettlPriceType.hpp"
#include "../common/Decimal.hpp"
#include "../enums/MdSecurityTradingStatus.hpp"
#include "../enums/PutOrCall.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../messages/ServerTcpMessage.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/LotTypeRulesGroups.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../structs/OptionUnderlyingsGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

class ServerTcpMessageVisitor;

// MDInstrumentDefinitionOption
class ServerPayloadMdInstrumentDefinitionOption : public ServerTcpMessage {
  public:
    // The code that selects this message
    static constexpr ServerTcpMessageCode message_type = TemplateId::MdInstrumentDefinitionOption;

    ServerPayloadMdInstrumentDefinitionOption() = default;
    ServerPayloadMdInstrumentDefinitionOption(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, PutOrCall put_or_call, const MaturityMonthYear& maturity_month_year, const std::string& currency, std::optional<Decimal> strike_price, const std::string& strike_currency, const std::string& settl_currency, std::optional<Decimal> min_cab_price, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, std::optional<Decimal> min_price_increment_optional, std::optional<Decimal> min_price_increment_amount, Decimal display_factor, std::optional<std::int8_t> tick_rule, std::optional<std::uint8_t> main_fraction, std::optional<std::uint8_t> sub_fraction, std::optional<std::uint8_t> price_display_format, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> trading_reference_price, const SettlPriceType& settl_price_type, std::optional<std::int32_t> cleared_volume, std::optional<std::int32_t> open_interest_qty, std::optional<Decimal> low_limit_price, std::optional<Decimal> high_limit_price, char user_defined_instrument, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups, const OptionUnderlyingsGroups& option_underlyings_groups);

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

    // Last Update Time: Timestamp of when the instrument was last added, modified or deleted
    std::chrono::nanoseconds last_update_time() const;
    void set_last_update_time(std::chrono::nanoseconds value);

    // Md Security Trading Status: Identifies the current state of the instrument. In Security
    // Definition message this tag is available in the Instrument Replay feed only
    std::optional<MdSecurityTradingStatus> md_security_trading_status() const;
    void set_md_security_trading_status(std::optional<MdSecurityTradingStatus> value);

    // Appl Id: The channel ID as defined in the XML Configuration file
    std::int16_t appl_id() const;
    void set_appl_id(std::int16_t value);

    // Market Segment Id: Last Security update action on Incremental feed, 'D' or 'M' is used
    // when a mid-week deletion or modification (i.e. extension) occurs
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

    // Asset: The underlying asset code also known as Product Code
    const std::string& asset() const;
    std::string& asset();
    void set_asset(const std::string& value);

    // Symbol: Instrument Name or Symbol
    const std::string& symbol() const;
    std::string& symbol();
    void set_symbol(const std::string& value);

    // Security Id: Unique instrument ID
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

    // Put Or Call: Indicates whether an option instrument is a put or call
    PutOrCall put_or_call() const;
    void set_put_or_call(PutOrCall value);

    // Maturity Month Year: MDInstrumentDefinitionFuture
    const MaturityMonthYear& maturity_month_year() const;
    MaturityMonthYear& maturity_month_year();
    void set_maturity_month_year(const MaturityMonthYear& value);

    // Currency: Identifies currency used for price
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Strike Price: Strike Price for an option instrument
    std::optional<Decimal> strike_price() const;
    void set_strike_price(std::optional<Decimal> value);

    // Strike Currency: Currency in which the StrikePrice is denominated
    const std::string& strike_currency() const;
    std::string& strike_currency();
    void set_strike_currency(const std::string& value);

    // Settl Currency: Identifies currency used for settlement, if different from trading
    // currency
    const std::string& settl_currency() const;
    std::string& settl_currency();
    void set_settl_currency(const std::string& value);

    // Min Cab Price: Defines cabinet price for outright options products
    std::optional<Decimal> min_cab_price() const;
    void set_min_cab_price(std::optional<Decimal> value);

    // Match Algorithm: Matching algorithm
    char match_algorithm() const;
    void set_match_algorithm(char value);

    // Min Trade Vol: The minimum trading volume for a security
    std::uint32_t min_trade_vol() const;
    void set_min_trade_vol(std::uint32_t value);

    // Max Trade Vol: The maximum trading volume for a security
    std::uint32_t max_trade_vol() const;
    void set_max_trade_vol(std::uint32_t value);

    // Min Price Increment Optional: Minimum constant tick for the instrument
    std::optional<Decimal> min_price_increment_optional() const;
    void set_min_price_increment_optional(std::optional<Decimal> value);

    // Min Price Increment Amount: Monetary value equivalent to the minimum price fluctuation
    std::optional<Decimal> min_price_increment_amount() const;
    void set_min_price_increment_amount(std::optional<Decimal> value);

    // Display Factor: Contains the multiplier to convert the CME Globex display price to the
    // conventional price
    Decimal display_factor() const;
    void set_display_factor(Decimal value);

    // Tick Rule: Tick Rule
    std::optional<std::int8_t> tick_rule() const;
    void set_tick_rule(std::optional<std::int8_t> value);

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

    // Settl Price Type: SettlPriceType bit set
    const SettlPriceType& settl_price_type() const;
    SettlPriceType& settl_price_type();
    void set_settl_price_type(const SettlPriceType& value);

    // Cleared Volume: The total cleared volume of instrument traded during the prior trading
    // session.
    std::optional<std::int32_t> cleared_volume() const;
    void set_cleared_volume(std::optional<std::int32_t> value);

    // Open Interest Qty: The total open interest for the market at the close of the prior
    // trading session.
    std::optional<std::int32_t> open_interest_qty() const;
    void set_open_interest_qty(std::optional<std::int32_t> value);

    // Low Limit Price: Allowable low limit price for the trading day
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // High Limit Price: Allowable high limit price for the trading day
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // User Defined Instrument: User-defined instruments flag
    char user_defined_instrument() const;
    void set_user_defined_instrument(char value);

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

    // Option Underlyings Groups: NoUnderlyings Block
    const OptionUnderlyingsGroups& option_underlyings_groups() const;
    OptionUnderlyingsGroups& option_underlyings_groups();
    void set_option_underlyings_groups(const OptionUnderlyingsGroups& value);

    // ServerTcpMessage
    ServerTcpMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(ServerTcpMessageVisitor& visitor) const override;
    std::unique_ptr<ServerTcpMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const ServerTcpMessage& other) const override;

    bool operator==(const ServerPayloadMdInstrumentDefinitionOption& other) const;
    bool operator!=(const ServerPayloadMdInstrumentDefinitionOption& other) const;

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
    PutOrCall put_or_call_{};
    MaturityMonthYear maturity_month_year_{};
    std::string currency_{};
    std::optional<Decimal> strike_price_{};
    std::string strike_currency_{};
    std::string settl_currency_{};
    std::optional<Decimal> min_cab_price_{};
    char match_algorithm_{};
    std::uint32_t min_trade_vol_{};
    std::uint32_t max_trade_vol_{};
    std::optional<Decimal> min_price_increment_optional_{};
    std::optional<Decimal> min_price_increment_amount_{};
    Decimal display_factor_{ 0, -7 };
    std::optional<std::int8_t> tick_rule_{};
    std::optional<std::uint8_t> main_fraction_{};
    std::optional<std::uint8_t> sub_fraction_{};
    std::optional<std::uint8_t> price_display_format_{};
    std::string unit_of_measure_{};
    std::optional<Decimal> unit_of_measure_qty_{};
    std::optional<Decimal> trading_reference_price_{};
    SettlPriceType settl_price_type_{};
    std::optional<std::int32_t> cleared_volume_{};
    std::optional<std::int32_t> open_interest_qty_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> high_limit_price_{};
    char user_defined_instrument_{};
    EventsGroups events_groups_{};
    FeedTypesGroups feed_types_groups_{};
    InstAttribGroups inst_attrib_groups_{};
    LotTypeRulesGroups lot_type_rules_groups_{};
    OptionUnderlyingsGroups option_underlyings_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_5
