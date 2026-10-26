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
#include "../enums/SecurityUpdateAction.hpp"
#include "../messages/MktdataPayload.hpp"
#include "../structs/EventsGroups.hpp"
#include "../structs/FeedTypesGroups.hpp"
#include "../structs/FxLotTypeRulesGroups.hpp"
#include "../structs/InstAttribGroups.hpp"
#include "../structs/MaturityMonthYear.hpp"
#include "../structs/TradingSessionsGroups.hpp"

namespace cme::globex::mdp3::sbe::v1_13 {

class MktdataPayloadVisitor;

// MDInstrumentDefinitionFX
class MdInstrumentDefinitionFx : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::MdInstrumentDefinitionFx;

    MdInstrumentDefinitionFx() = default;
    MdInstrumentDefinitionFx(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const std::string& currency, const std::string& settl_currency, const std::string& price_quote_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, Decimal min_price_increment_ex, Decimal display_factor, std::uint8_t price_precision, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, char user_defined_instrument, const std::string& financial_instrument_full_name, const std::string& fx_currency_symbol, const std::string& settl_type, std::uint16_t intervening_days, const std::string& fx_benchmark_rate_fix, const std::string& rate_source, const std::string& fix_rate_local_time, const std::string& fix_rate_local_time_zone, std::uint32_t min_quote_life, Decimal max_price_discretion_offset, std::optional<std::uint64_t> instrument_guid, const MaturityMonthYear& maturity_month_year, const std::string& settlement_locale, std::optional<Decimal> alt_min_price_increment, std::optional<std::uint32_t> alt_min_quote_life, std::optional<Decimal> alt_price_increment_constraint, std::optional<Decimal> max_bid_ask_constraint, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const FxLotTypeRulesGroups& fx_lot_type_rules_groups, const TradingSessionsGroups& trading_sessions_groups);

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

    // Price Quote Currency: Local (counter) currency
    const std::string& price_quote_currency() const;
    std::string& price_quote_currency();
    void set_price_quote_currency(const std::string& value);

    // Match Algorithm: Matching algorithm
    char match_algorithm() const;
    void set_match_algorithm(char value);

    // Min Trade Vol: The minimum trading volume for a security
    std::uint32_t min_trade_vol() const;
    void set_min_trade_vol(std::uint32_t value);

    // Max Trade Vol: The maximum trading volume for a security
    std::uint32_t max_trade_vol() const;
    void set_max_trade_vol(std::uint32_t value);

    // Min Price Increment Ex: Minimum constant tick for the instrument, sent only if
    // instrument is non-VTT (Variable Tick table) eligible
    Decimal min_price_increment_ex() const;
    void set_min_price_increment_ex(Decimal value);

    // Display Factor: Contains the multiplier to convert the CME Globex display price to the
    // conventional price
    Decimal display_factor() const;
    void set_display_factor(Decimal value);

    // Price Precision: Specifies price decimal precision for EBS instrument
    std::uint8_t price_precision() const;
    void set_price_precision(std::uint8_t value);

    // Unit Of Measure: Unit of measure for the products' original contract size. This will be
    // populated for all products listed on CME Globex
    const std::string& unit_of_measure() const;
    std::string& unit_of_measure();
    void set_unit_of_measure(const std::string& value);

    // Unit Of Measure Qty: This field contains the contract size for each instrument. Used in
    // combination with tag 996-UnitofMeasure
    std::optional<Decimal> unit_of_measure_qty() const;
    void set_unit_of_measure_qty(std::optional<Decimal> value);

    // High Limit Price: Upper price threshold for the instrument
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: Lower price threshold for the instrument
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: Differential value for price banding
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // User Defined Instrument: User-defined instruments flag
    char user_defined_instrument() const;
    void set_user_defined_instrument(char value);

    // Financial Instrument Full Name: Long name of the instrument
    const std::string& financial_instrument_full_name() const;
    std::string& financial_instrument_full_name();
    void set_financial_instrument_full_name(const std::string& value);

    // Fx Currency Symbol: Base/Local. Denotes the currency pair in CCY1/CCY2 convention
    const std::string& fx_currency_symbol() const;
    std::string& fx_currency_symbol();
    void set_fx_currency_symbol(const std::string& value);

    // Settl Type: For SPOTs will contain 0. For Fixed date NDFs will contain the value 'B'.
    // For the standard NDFs tenors expressed using Dx, Mx, Wx, and Yx values, where 'x' does
    // not denote business days, but calendar days
    const std::string& settl_type() const;
    std::string& settl_type();
    void set_settl_type(const std::string& value);

    // Intervening Days: For SPOT, number of business days between trade date and value
    // (settlement) date. For NDF, number of business days between NDF valuation (fixing) and
    // settlement
    std::uint16_t intervening_days() const;
    void set_intervening_days(std::uint16_t value);

    // Fx Benchmark Rate Fix: Fixing Rate Description
    const std::string& fx_benchmark_rate_fix() const;
    std::string& fx_benchmark_rate_fix();
    void set_fx_benchmark_rate_fix(const std::string& value);

    // Rate Source: Fixing Rate Source
    const std::string& rate_source() const;
    std::string& rate_source();
    void set_rate_source(const std::string& value);

    // Fix Rate Local Time: Fixing Rate Local Time, denoted in HH:MM:SS format
    const std::string& fix_rate_local_time() const;
    std::string& fix_rate_local_time();
    void set_fix_rate_local_time(const std::string& value);

    // Fix Rate Local Time Zone: Fixing Rate Local Time Zone corresponding to Fixing Local
    // Time.
    const std::string& fix_rate_local_time_zone() const;
    std::string& fix_rate_local_time_zone();
    void set_fix_rate_local_time_zone(const std::string& value);

    // Min Quote Life: Minimum Quote Life in number of microseconds
    std::uint32_t min_quote_life() const;
    void set_min_quote_life(std::uint32_t value);

    // Max Price Discretion Offset: Max allowed discretionary offset from Limit order price.
    // When the value in this field = 0, discretionary price cannot be submitted for the
    // instrument
    Decimal max_price_discretion_offset() const;
    void set_max_price_discretion_offset(Decimal value);

    // Instrument Guid: External unique instrument ID
    std::optional<std::uint64_t> instrument_guid() const;
    void set_instrument_guid(std::optional<std::uint64_t> value);

    // Maturity Month Year: MDInstrumentDefinitionFuture
    const MaturityMonthYear& maturity_month_year() const;
    MaturityMonthYear& maturity_month_year();
    void set_maturity_month_year(const MaturityMonthYear& value);

    // Settlement Locale: Settlement Locale. Optionally used to differentiate settlement
    // location
    const std::string& settlement_locale() const;
    std::string& settlement_locale();
    void set_settlement_locale(const std::string& value);

    // Alt Min Price Increment: New sub-tick which is only available for order entry when
    // certain conditions are met, tick value which corresponds to the Alt Min Quote Life
    std::optional<Decimal> alt_min_price_increment() const;
    void set_alt_min_price_increment(std::optional<Decimal> value);

    // Alt Min Quote Life: MQL duration in number of microseconds applied to orders at
    // AltMinPriceIncrement
    std::optional<std::uint32_t> alt_min_quote_life() const;
    void set_alt_min_quote_life(std::optional<std::uint32_t> value);

    // Alt Price Increment Constraint: Minimum price offset better than the best Standard Tick
    // order for an order to be allowed into the market
    std::optional<Decimal> alt_price_increment_constraint() const;
    void set_alt_price_increment_constraint(std::optional<Decimal> value);

    // Max Bid Ask Constraint: Maximum bid/ask spread for which sub-tick orders will be
    // accepted (Sub tick orders will be rejected if bid/ask spread is greater than this value)
    std::optional<Decimal> max_bid_ask_constraint() const;
    void set_max_bid_ask_constraint(std::optional<Decimal> value);

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

    // Fx Lot Type Rules Groups: NoLotTypeRules Block
    const FxLotTypeRulesGroups& fx_lot_type_rules_groups() const;
    FxLotTypeRulesGroups& fx_lot_type_rules_groups();
    void set_fx_lot_type_rules_groups(const FxLotTypeRulesGroups& value);

    // Trading Sessions Groups: NoTradingSessions Block
    const TradingSessionsGroups& trading_sessions_groups() const;
    TradingSessionsGroups& trading_sessions_groups();
    void set_trading_sessions_groups(const TradingSessionsGroups& value);

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

    bool operator==(const MdInstrumentDefinitionFx& other) const;
    bool operator!=(const MdInstrumentDefinitionFx& other) const;

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
    std::string price_quote_currency_{};
    char match_algorithm_{};
    std::uint32_t min_trade_vol_{};
    std::uint32_t max_trade_vol_{};
    Decimal min_price_increment_ex_{ 0, -9 };
    Decimal display_factor_{ 0, -9 };
    std::uint8_t price_precision_{};
    std::string unit_of_measure_{};
    std::optional<Decimal> unit_of_measure_qty_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    char user_defined_instrument_{};
    std::string financial_instrument_full_name_{};
    std::string fx_currency_symbol_{};
    std::string settl_type_{};
    std::uint16_t intervening_days_{};
    std::string fx_benchmark_rate_fix_{};
    std::string rate_source_{};
    std::string fix_rate_local_time_{};
    std::string fix_rate_local_time_zone_{};
    std::uint32_t min_quote_life_{};
    Decimal max_price_discretion_offset_{ 0, -9 };
    std::optional<std::uint64_t> instrument_guid_{};
    MaturityMonthYear maturity_month_year_{};
    std::string settlement_locale_{};
    std::optional<Decimal> alt_min_price_increment_{};
    std::optional<std::uint32_t> alt_min_quote_life_{};
    std::optional<Decimal> alt_price_increment_constraint_{};
    std::optional<Decimal> max_bid_ask_constraint_{};
    EventsGroups events_groups_{};
    FeedTypesGroups feed_types_groups_{};
    InstAttribGroups inst_attrib_groups_{};
    FxLotTypeRulesGroups fx_lot_type_rules_groups_{};
    TradingSessionsGroups trading_sessions_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_13
