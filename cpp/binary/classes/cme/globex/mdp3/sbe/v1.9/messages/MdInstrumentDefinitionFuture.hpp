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
#include "../structs/LotTypeRulesGroups.hpp"
#include "../structs/MaturityMonthYear.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

class MktdataPayloadVisitor;

// MDInstrumentDefinitionFuture
class MdInstrumentDefinitionFuture : public MktdataPayload {
  public:
    // The code that selects this message
    static constexpr MktdataPayloadCode message_type = TemplateId::MdInstrumentDefinitionFuture;

    MdInstrumentDefinitionFuture() = default;
    MdInstrumentDefinitionFuture(const MatchEventIndicator& match_event_indicator, std::optional<std::uint32_t> tot_num_reports_optional, SecurityUpdateAction security_update_action, std::chrono::nanoseconds last_update_time, std::optional<MdSecurityTradingStatus> md_security_trading_status, std::int16_t appl_id, std::uint8_t market_segment_id, std::uint8_t underlying_product, const std::string& security_exchange, const std::string& security_group, const std::string& asset, const std::string& symbol, std::int32_t security_id, const std::string& security_type, const std::string& cfi_code, const MaturityMonthYear& maturity_month_year, const std::string& currency, const std::string& settl_currency, char match_algorithm, std::uint32_t min_trade_vol, std::uint32_t max_trade_vol, Decimal min_price_increment_ex, Decimal display_factor_ex, std::optional<std::uint8_t> main_fraction, std::optional<std::uint8_t> sub_fraction, std::optional<std::uint8_t> price_display_format, const std::string& unit_of_measure, std::optional<Decimal> unit_of_measure_qty_ex, std::optional<Decimal> trading_reference_price_ex, const SettlPriceType& settl_price_type, std::optional<std::int32_t> open_interest_qty, std::optional<std::int32_t> cleared_volume, std::optional<Decimal> high_limit_price_ex, std::optional<Decimal> low_limit_price_ex, std::optional<Decimal> max_price_variation_ex, std::optional<std::int32_t> decay_quantity, std::optional<std::uint16_t> decay_start_date, std::optional<std::int32_t> original_contract_size, std::optional<std::int32_t> contract_multiplier, std::optional<std::int8_t> contract_multiplier_unit, std::optional<std::int8_t> flow_schedule_type, std::optional<Decimal> min_price_increment_amount_ex, char user_defined_instrument, std::optional<std::uint16_t> trading_reference_date, const EventsGroups& events_groups, const FeedTypesGroups& feed_types_groups, const InstAttribGroups& inst_attrib_groups, const LotTypeRulesGroups& lot_type_rules_groups);

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

    // Maturity Month Year: MDInstrumentDefinitionFuture
    const MaturityMonthYear& maturity_month_year() const;
    MaturityMonthYear& maturity_month_year();
    void set_maturity_month_year(const MaturityMonthYear& value);

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

    // Min Price Increment Ex: Minimum constant tick for the instrument, sent only if
    // instrument is non-VTT (Variable Tick table) eligible
    Decimal min_price_increment_ex() const;
    void set_min_price_increment_ex(Decimal value);

    // Display Factor Ex: Contains the multiplier to convert the CME Globex display price to
    // the conventional price
    Decimal display_factor_ex() const;
    void set_display_factor_ex(Decimal value);

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

    // Unit Of Measure Qty Ex: This field contains the contract size for each instrument. Used
    // in combination with tag 996-UnitofMeasure
    std::optional<Decimal> unit_of_measure_qty_ex() const;
    void set_unit_of_measure_qty_ex(std::optional<Decimal> value);

    // Trading Reference Price Ex: Reference price for prelisted instruments or the last
    // calculated Settlement whether it be Theoretical, Preliminary or a Final Settle of the
    // session.
    std::optional<Decimal> trading_reference_price_ex() const;
    void set_trading_reference_price_ex(std::optional<Decimal> value);

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

    // High Limit Price Ex: Upper price threshold for the instrument
    std::optional<Decimal> high_limit_price_ex() const;
    void set_high_limit_price_ex(std::optional<Decimal> value);

    // Low Limit Price Ex: Lower price threshold for the instrument
    std::optional<Decimal> low_limit_price_ex() const;
    void set_low_limit_price_ex(std::optional<Decimal> value);

    // Max Price Variation Ex: Differential value for price banding
    std::optional<Decimal> max_price_variation_ex() const;
    void set_max_price_variation_ex(std::optional<Decimal> value);

    // Decay Quantity: Indicates the quantity that a contract will decay daily by once the
    // decay start date is reached
    std::optional<std::int32_t> decay_quantity() const;
    void set_decay_quantity(std::optional<std::int32_t> value);

    // Decay Start Date: Indicates the date at which a decaying contract will begin to decay
    std::optional<std::uint16_t> decay_start_date() const;
    void set_decay_start_date(std::optional<std::uint16_t> value);

    // Original Contract Size: Fixed contract value assigned to each product
    std::optional<std::int32_t> original_contract_size() const;
    void set_original_contract_size(std::optional<std::int32_t> value);

    // Contract Multiplier: Number of deliverable units per instrument, e.g., peak days in
    // maturity month or number of calendar days in maturity month
    std::optional<std::int32_t> contract_multiplier() const;
    void set_contract_multiplier(std::optional<std::int32_t> value);

    // Contract Multiplier Unit: Indicates the type of multiplier being applied to the product.
    // Optionally used in combination with tag 231-ContractMultiplier
    std::optional<std::int8_t> contract_multiplier_unit() const;
    void set_contract_multiplier_unit(std::optional<std::int8_t> value);

    // Flow Schedule Type: The schedule according to which the electricity is delivered in a
    // physical contract, or priced in a financial contract. Specifies whether the contract is
    // defined according to the Easter Peak, Eastern Off-Peak, Western Peak or Western
    // Off-Peak.
    std::optional<std::int8_t> flow_schedule_type() const;
    void set_flow_schedule_type(std::optional<std::int8_t> value);

    // Min Price Increment Amount Ex: Monetary value equivalent to the minimum price
    // fluctuation
    std::optional<Decimal> min_price_increment_amount_ex() const;
    void set_min_price_increment_amount_ex(std::optional<Decimal> value);

    // User Defined Instrument: User-defined instruments flag
    char user_defined_instrument() const;
    void set_user_defined_instrument(char value);

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

    bool operator==(const MdInstrumentDefinitionFuture& other) const;
    bool operator!=(const MdInstrumentDefinitionFuture& other) const;

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
    MaturityMonthYear maturity_month_year_{};
    std::string currency_{};
    std::string settl_currency_{};
    char match_algorithm_{};
    std::uint32_t min_trade_vol_{};
    std::uint32_t max_trade_vol_{};
    Decimal min_price_increment_ex_{ 0, -9 };
    Decimal display_factor_ex_{ 0, -9 };
    std::optional<std::uint8_t> main_fraction_{};
    std::optional<std::uint8_t> sub_fraction_{};
    std::optional<std::uint8_t> price_display_format_{};
    std::string unit_of_measure_{};
    std::optional<Decimal> unit_of_measure_qty_ex_{};
    std::optional<Decimal> trading_reference_price_ex_{};
    SettlPriceType settl_price_type_{};
    std::optional<std::int32_t> open_interest_qty_{};
    std::optional<std::int32_t> cleared_volume_{};
    std::optional<Decimal> high_limit_price_ex_{};
    std::optional<Decimal> low_limit_price_ex_{};
    std::optional<Decimal> max_price_variation_ex_{};
    std::optional<std::int32_t> decay_quantity_{};
    std::optional<std::uint16_t> decay_start_date_{};
    std::optional<std::int32_t> original_contract_size_{};
    std::optional<std::int32_t> contract_multiplier_{};
    std::optional<std::int8_t> contract_multiplier_unit_{};
    std::optional<std::int8_t> flow_schedule_type_{};
    std::optional<Decimal> min_price_increment_amount_ex_{};
    char user_defined_instrument_{};
    std::optional<std::uint16_t> trading_reference_date_{};
    EventsGroups events_groups_{};
    FeedTypesGroups feed_types_groups_{};
    InstAttribGroups inst_attrib_groups_{};
    LotTypeRulesGroups lot_type_rules_groups_{};
};

} // namespace cme::globex::mdp3::sbe::v1_9
