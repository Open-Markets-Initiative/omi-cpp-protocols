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
#include "../enums/SecurityUpdateAction.hpp"
#include "../messages/MktdataPayload.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/LegacyLegsGroups.hpp"
#include "../structs/LotTypeRulesGroups.hpp"
#include "../structs/MaturityMonthYear.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

class MktdataPayloadVisitor;

// MDInstrumentDefinitionSpread
class MdInstrumentDefinitionSpreadLegacy : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::MdInstrumentDefinitionSpreadLegacy;

    MdInstrumentDefinitionSpreadLegacy() = default;
    MdInstrumentDefinitionSpreadLegacy(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::optional<std::uint8_t> underlying_product_optional, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const MaturityMonthYear& maturity_month_year, const std::string& currency, const std::string& security_sub_type, char user_defined_instrument, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, Decimal min_price_increment, Decimal display_factor, std::optional<std::uint8_t> price_display_format, std::optional<Decimal> price_ratio, std::optional<std::int8_t> tick_rule, const std::string& unit_of_measure, std::optional<Decimal> trading_reference_price, const SettlPriceType& settl_price_type, std::optional<std::int32_t> open_interest_qty, std::optional<std::int32_t> cleared_volume, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::optional<std::uint8_t> main_fraction, std::optional<std::uint8_t> sub_fraction, std::optional<std::uint16_t> trading_reference_date, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups, const LegacyLegsGroups& legacy_legs_groups);

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

    // Market Segment Id: Identifies the market segment, populated for all CME Globex
    // instruments
    std::uint8_t market_segment_id() const;
    void set_market_segment_id(std::uint8_t value);

    // Underlying Product Optional: Product complex
    std::optional<std::uint8_t> underlying_product_optional() const;
    void set_underlying_product_optional(std::optional<std::uint8_t> value);

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

    // Maturity Month Year: MDInstrumentDefinitionFuture
    const MaturityMonthYear& maturity_month_year() const;
    MaturityMonthYear& maturity_month_year();
    void set_maturity_month_year(const MaturityMonthYear& value);

    // Currency: Identifies currency used for price
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Security Sub Type: Strategy type
    const std::string& security_sub_type() const;
    std::string& security_sub_type();
    void set_security_sub_type(const std::string& value);

    // User Defined Instrument: User-defined instruments flag
    char user_defined_instrument() const;
    void set_user_defined_instrument(char value);

    // Match Algorithm: Matching algorithm
    char match_algorithm() const;
    void set_match_algorithm(char value);

    // Min Trade Vol: The minimum trading volume for a security
    std::uint32_t min_trade_vol() const;
    void set_min_trade_vol(std::uint32_t value);

    // Max Trade Vol: The maximum trading volume for a security
    std::uint32_t max_trade_vol() const;
    void set_max_trade_vol(std::uint32_t value);

    // Min Price Increment: Minimum constant tick for the instrument, sent only if instrument
    // is non-VTT (Variable Tick table) eligible
    Decimal min_price_increment() const;
    void set_min_price_increment(Decimal value);

    // Display Factor: Contains the multiplier to convert the CME Globex display price to the
    // conventional price
    Decimal display_factor() const;
    void set_display_factor(Decimal value);

    // Price Display Format: Number of decimals in fractional display price
    std::optional<std::uint8_t> price_display_format() const;
    void set_price_display_format(std::optional<std::uint8_t> value);

    // Price Ratio: Used for price calculation in spread and leg pricing
    std::optional<Decimal> price_ratio() const;
    void set_price_ratio(std::optional<Decimal> value);

    // Tick Rule: Tick Rule
    std::optional<std::int8_t> tick_rule() const;
    void set_tick_rule(std::optional<std::int8_t> value);

    // Unit Of Measure: Unit of measure for the products' original contract size. This will be
    // populated for all products listed on CME Globex
    const std::string& unit_of_measure() const;
    std::string& unit_of_measure();
    void set_unit_of_measure(const std::string& value);

    // Trading Reference Price: Reference price for prelisted instruments or the last
    // calculated Settlement whether it be Theoretical, Preliminary or a Final Settle of the
    // session.
    std::optional<Decimal> trading_reference_price() const;
    void set_trading_reference_price(std::optional<Decimal> value);

    // Settl Price Type: SettlPriceType bit set
    const SettlPriceType& settl_price_type() const;
    SettlPriceType& settl_price_type();
    void set_settl_price_type(const SettlPriceType& value);

    // Open Interest Qty: The total open interest for the market at the close of the prior
    // trading session.
    std::optional<std::int32_t> open_interest_qty() const;
    void set_open_interest_qty(std::optional<std::int32_t> value);

    // Cleared Volume: The total cleared volume of instrument traded during the prior trading
    // session.
    std::optional<std::int32_t> cleared_volume() const;
    void set_cleared_volume(std::optional<std::int32_t> value);

    // High Limit Price: Allowable high limit price for the trading day
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: Allowable low limit price for the trading day
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: Differential value for price banding.
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // Main Fraction: Price Denominator of Main Fraction
    std::optional<std::uint8_t> main_fraction() const;
    void set_main_fraction(std::optional<std::uint8_t> value);

    // Sub Fraction: Price Denominator of Sub Fraction
    std::optional<std::uint8_t> sub_fraction() const;
    void set_sub_fraction(std::optional<std::uint8_t> value);

    // Trading Reference Date: Indicates session date corresponding to the settlement price in
    // tag 1150-TradingReferencePrice
    std::optional<std::uint16_t> trading_reference_date() const;
    void set_trading_reference_date(std::optional<std::uint16_t> value);

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

    // Legacy Legs Groups: NoLegs Block
    const LegacyLegsGroups& legacy_legs_groups() const;
    LegacyLegsGroups& legacy_legs_groups();
    void set_legacy_legs_groups(const LegacyLegsGroups& value);

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

    bool operator==(const MdInstrumentDefinitionSpreadLegacy& other) const;
    bool operator!=(const MdInstrumentDefinitionSpreadLegacy& other) const;

  private:
    MatchEventIndicator match_event_indicator_{};
    std::optional<std::uint32_t> tot_num_reports_optional_{};
    SecurityUpdateAction security_update_action_{};
    std::chrono::nanoseconds last_update_time_{};
    std::optional<MdSecurityTradingStatus> md_security_trading_status_{};
    std::int16_t appl_id_{};
    std::uint8_t market_segment_id_{};
    std::optional<std::uint8_t> underlying_product_optional_{};
    std::string security_exchange_{};
    std::string security_group_{};
    std::string asset_{};
    std::string symbol_{};
    std::int32_t security_id_{};
    std::string security_type_{};
    std::string cfi_code_{};
    MaturityMonthYear maturity_month_year_{};
    std::string currency_{};
    std::string security_sub_type_{};
    char user_defined_instrument_{};
    char match_algorithm_{};
    std::uint32_t min_trade_vol_{};
    std::uint32_t max_trade_vol_{};
    Decimal min_price_increment_{ 0, -7 };
    Decimal display_factor_{ 0, -7 };
    std::optional<std::uint8_t> price_display_format_{};
    std::optional<Decimal> price_ratio_{};
    std::optional<std::int8_t> tick_rule_{};
    std::string unit_of_measure_{};
    std::optional<Decimal> trading_reference_price_{};
    SettlPriceType settl_price_type_{};
    std::optional<std::int32_t> open_interest_qty_{};
    std::optional<std::int32_t> cleared_volume_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    std::optional<std::uint8_t> main_fraction_{};
    std::optional<std::uint8_t> sub_fraction_{};
    std::optional<std::uint16_t> trading_reference_date_{};
    EventsGroups events_groups_{};
    FeedTypesGroups feed_types_groups_{};
    InstAttribGroups inst_attrib_groups_{};
    LotTypeRulesGroups lot_type_rules_groups_{};
    LegacyLegsGroups legacy_legs_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_9
