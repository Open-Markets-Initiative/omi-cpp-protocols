#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/InstrumentClass.hpp"
#include "../enums/MatchAlgorithm.hpp"
#include "../enums/SecurityUpdateAction.hpp"
#include "../enums/UserDefinedInstrument.hpp"
#include "../messages/GatewayMessage.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

class GatewayMessageVisitor;

// A definition of an instrument; the record of the definition schema
class RecordBodyInstrumentDefMsg : public GatewayMessage {
  public:
    // The code that selects this message
    static constexpr GatewayMessageCode message_type = Rtype::InstrumentDefinition;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 344;

    RecordBodyInstrumentDefMsg() = default;
    RecordBodyInstrumentDefMsg(std::optional<std::chrono::nanoseconds> ts_recv, std::optional<Decimal> min_price_increment, std::optional<Decimal> display_factor, std::optional<std::chrono::nanoseconds> expiration, std::optional<std::chrono::nanoseconds> activation, std::optional<Decimal> high_limit_price, std::optional<Decimal> low_limit_price, std::optional<Decimal> max_price_variation, std::optional<Decimal> trading_reference_price, std::optional<Decimal> unit_of_measure_qty, std::optional<Decimal> min_price_increment_amount, std::optional<Decimal> price_ratio, std::int32_t inst_attrib_value, std::uint32_t underlying_id, std::uint32_t raw_instrument_id, std::int32_t market_depth_implied, std::int32_t market_depth, std::uint32_t market_segment_id, std::uint32_t max_trade_vol, std::int32_t min_lot_size, std::int32_t min_lot_size_block, std::int32_t min_lot_size_round_lot, std::uint32_t min_trade_vol, const std::array<std::byte, 4>& reserved_4, std::int32_t contract_multiplier, std::int32_t decay_quantity, std::int32_t original_contract_size, const std::array<std::byte, 4>& second_reserved_4, std::uint16_t trading_reference_date, std::int16_t appl_id, std::uint16_t maturity_year, std::uint16_t decay_start_date, std::uint16_t channel, const std::string& currency, const std::string& settl_currency, const std::string& secsubtype, const std::string& raw_symbol, const std::string& group, const std::string& exchange, const std::string& asset, const std::string& cfi, const std::string& security_type, const std::string& unit_of_measure, const std::string& underlying, const std::string& strike_price_currency, InstrumentClass instrument_class, const std::array<std::byte, 2>& reserved_2, std::optional<Decimal> strike_price, const std::array<std::byte, 6>& reserved_6, MatchAlgorithm match_algorithm, std::uint8_t md_security_trading_status, std::uint8_t main_fraction, std::uint8_t price_display_format, std::uint8_t settl_price_type, std::uint8_t sub_fraction, std::uint8_t underlying_product, SecurityUpdateAction security_update_action, std::uint8_t maturity_month, std::uint8_t maturity_day, std::uint8_t maturity_week, UserDefinedInstrument user_defined_instrument, std::int8_t contract_multiplier_unit, std::int8_t flow_schedule_type, std::uint8_t tick_rule, const std::array<std::byte, 3>& dummy_3);

    // Ts Recv: The capture-server-received timestamp expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> ts_recv() const;
    void set_ts_recv(std::optional<std::chrono::nanoseconds> value);

    // Min Price Increment: The min price increment, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> min_price_increment() const;
    void set_min_price_increment(std::optional<Decimal> value);

    // Display Factor: The display factor, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> display_factor() const;
    void set_display_factor(std::optional<Decimal> value);

    // Expiration: The last eligible trade time expressed as the number of nanoseconds since
    // the UNIX epoch
    std::optional<std::chrono::nanoseconds> expiration() const;
    void set_expiration(std::optional<std::chrono::nanoseconds> value);

    // Activation: The time of instrument activation expressed as the number of nanoseconds
    // since the UNIX epoch
    std::optional<std::chrono::nanoseconds> activation() const;
    void set_activation(std::optional<std::chrono::nanoseconds> value);

    // High Limit Price: The high limit price, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> high_limit_price() const;
    void set_high_limit_price(std::optional<Decimal> value);

    // Low Limit Price: The low limit price, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> low_limit_price() const;
    void set_low_limit_price(std::optional<Decimal> value);

    // Max Price Variation: The max price variation, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> max_price_variation() const;
    void set_max_price_variation(std::optional<Decimal> value);

    // Trading Reference Price: The trading session settlement price on trading_reference_date,
    // where every 1 unit corresponds to 1e-9
    std::optional<Decimal> trading_reference_price() const;
    void set_trading_reference_price(std::optional<Decimal> value);

    // Unit Of Measure Qty: The unit of measure qty, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> unit_of_measure_qty() const;
    void set_unit_of_measure_qty(std::optional<Decimal> value);

    // Min Price Increment Amount: The min price increment amount, where every 1 unit
    // corresponds to 1e-9
    std::optional<Decimal> min_price_increment_amount() const;
    void set_min_price_increment_amount(std::optional<Decimal> value);

    // Price Ratio: The price ratio, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> price_ratio() const;
    void set_price_ratio(std::optional<Decimal> value);

    // Inst Attrib Value: A bitmap of instrument eligibility attributes; venue-specific
    std::int32_t inst_attrib_value() const;
    void set_inst_attrib_value(std::int32_t value);

    // Underlying Id: The underlying id
    std::uint32_t underlying_id() const;
    void set_underlying_id(std::uint32_t value);

    // Raw Instrument Id: The instrument ID assigned by the publisher; may be the same as
    // instrument_id
    std::uint32_t raw_instrument_id() const;
    void set_raw_instrument_id(std::uint32_t value);

    // Market Depth Implied: The market depth implied
    std::int32_t market_depth_implied() const;
    void set_market_depth_implied(std::int32_t value);

    // Market Depth: The market depth
    std::int32_t market_depth() const;
    void set_market_depth(std::int32_t value);

    // Market Segment Id: The market segment id
    std::uint32_t market_segment_id() const;
    void set_market_segment_id(std::uint32_t value);

    // Max Trade Vol: The max trade vol
    std::uint32_t max_trade_vol() const;
    void set_max_trade_vol(std::uint32_t value);

    // Min Lot Size: The min lot size
    std::int32_t min_lot_size() const;
    void set_min_lot_size(std::int32_t value);

    // Min Lot Size Block: The min lot size block
    std::int32_t min_lot_size_block() const;
    void set_min_lot_size_block(std::int32_t value);

    // Min Lot Size Round Lot: The min lot size round lot
    std::int32_t min_lot_size_round_lot() const;
    void set_min_lot_size_round_lot(std::int32_t value);

    // Min Trade Vol: The min trade vol
    std::uint32_t min_trade_vol() const;
    void set_min_trade_vol(std::uint32_t value);

    // Reserved 4: Reserved, 4 bytes
    const std::array<std::byte, 4>& reserved_4() const;
    std::array<std::byte, 4>& reserved_4();
    void set_reserved_4(const std::array<std::byte, 4>& value);

    // Contract Multiplier: The contract multiplier
    std::int32_t contract_multiplier() const;
    void set_contract_multiplier(std::int32_t value);

    // Decay Quantity: The decay quantity
    std::int32_t decay_quantity() const;
    void set_decay_quantity(std::int32_t value);

    // Original Contract Size: The original contract size
    std::int32_t original_contract_size() const;
    void set_original_contract_size(std::int32_t value);

    // Second Reserved 4: Reserved, 4 bytes
    const std::array<std::byte, 4>& second_reserved_4() const;
    std::array<std::byte, 4>& second_reserved_4();
    void set_second_reserved_4(const std::array<std::byte, 4>& value);

    // Trading Reference Date: The trading session date corresponding to the settlement price
    // in trading_reference_price, in number of days since the UNIX epoch
    std::uint16_t trading_reference_date() const;
    void set_trading_reference_date(std::uint16_t value);

    // Appl Id: The appl id
    std::int16_t appl_id() const;
    void set_appl_id(std::int16_t value);

    // Maturity Year: The maturity year
    std::uint16_t maturity_year() const;
    void set_maturity_year(std::uint16_t value);

    // Decay Start Date: The decay start date
    std::uint16_t decay_start_date() const;
    void set_decay_start_date(std::uint16_t value);

    // Channel: The channel ID assigned by Databento as an incrementing integer starting at
    // zero
    std::uint16_t channel() const;
    void set_channel(std::uint16_t value);

    // Currency: The currency
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Settl Currency: The settl currency
    const std::string& settl_currency() const;
    std::string& settl_currency();
    void set_settl_currency(const std::string& value);

    // Secsubtype: The secsubtype
    const std::string& secsubtype() const;
    std::string& secsubtype();
    void set_secsubtype(const std::string& value);

    // Raw Symbol: The raw symbol
    const std::string& raw_symbol() const;
    std::string& raw_symbol();
    void set_raw_symbol(const std::string& value);

    // Group: The group
    const std::string& group() const;
    std::string& group();
    void set_group(const std::string& value);

    // Exchange: The exchange
    const std::string& exchange() const;
    std::string& exchange();
    void set_exchange(const std::string& value);

    // Asset: The asset
    const std::string& asset() const;
    std::string& asset();
    void set_asset(const std::string& value);

    // Cfi: The cfi
    const std::string& cfi() const;
    std::string& cfi();
    void set_cfi(const std::string& value);

    // Security Type: The security type
    const std::string& security_type() const;
    std::string& security_type();
    void set_security_type(const std::string& value);

    // Unit Of Measure: The unit of measure
    const std::string& unit_of_measure() const;
    std::string& unit_of_measure();
    void set_unit_of_measure(const std::string& value);

    // Underlying: The underlying
    const std::string& underlying() const;
    std::string& underlying();
    void set_underlying(const std::string& value);

    // Strike Price Currency: The strike price currency
    const std::string& strike_price_currency() const;
    std::string& strike_price_currency();
    void set_strike_price_currency(const std::string& value);

    // Instrument Class: The classification of the instrument
    InstrumentClass instrument_class() const;
    void set_instrument_class(InstrumentClass value);

    // Reserved 2: Reserved, 2 bytes
    const std::array<std::byte, 2>& reserved_2() const;
    std::array<std::byte, 2>& reserved_2();
    void set_reserved_2(const std::array<std::byte, 2>& value);

    // Strike Price: The strike price, where every 1 unit corresponds to 1e-9
    std::optional<Decimal> strike_price() const;
    void set_strike_price(std::optional<Decimal> value);

    // Reserved 6: Reserved, 6 bytes
    const std::array<std::byte, 6>& reserved_6() const;
    std::array<std::byte, 6>& reserved_6();
    void set_reserved_6(const std::array<std::byte, 6>& value);

    // Match Algorithm: The matching algorithm used for the instrument, typically FIFO
    MatchAlgorithm match_algorithm() const;
    void set_match_algorithm(MatchAlgorithm value);

    // Md Security Trading Status: The current trading state of the instrument
    std::uint8_t md_security_trading_status() const;
    void set_md_security_trading_status(std::uint8_t value);

    // Main Fraction: The main fraction
    std::uint8_t main_fraction() const;
    void set_main_fraction(std::uint8_t value);

    // Price Display Format: The price display format
    std::uint8_t price_display_format() const;
    void set_price_display_format(std::uint8_t value);

    // Settl Price Type: The type indicators for the settlement price, as a bitmap
    std::uint8_t settl_price_type() const;
    void set_settl_price_type(std::uint8_t value);

    // Sub Fraction: The sub fraction
    std::uint8_t sub_fraction() const;
    void set_sub_fraction(std::uint8_t value);

    // Underlying Product: The underlying product
    std::uint8_t underlying_product() const;
    void set_underlying_product(std::uint8_t value);

    // Security Update Action: Indicates if the instrument definition has been added, modified,
    // or deleted
    SecurityUpdateAction security_update_action() const;
    void set_security_update_action(SecurityUpdateAction value);

    // Maturity Month: The maturity month
    std::uint8_t maturity_month() const;
    void set_maturity_month(std::uint8_t value);

    // Maturity Day: The maturity day
    std::uint8_t maturity_day() const;
    void set_maturity_day(std::uint8_t value);

    // Maturity Week: The maturity week
    std::uint8_t maturity_week() const;
    void set_maturity_week(std::uint8_t value);

    // User Defined Instrument: Indicates if the instrument is user defined
    UserDefinedInstrument user_defined_instrument() const;
    void set_user_defined_instrument(UserDefinedInstrument value);

    // Contract Multiplier Unit: The contract multiplier unit
    std::int8_t contract_multiplier_unit() const;
    void set_contract_multiplier_unit(std::int8_t value);

    // Flow Schedule Type: The flow schedule type
    std::int8_t flow_schedule_type() const;
    void set_flow_schedule_type(std::int8_t value);

    // Tick Rule: The tick rule
    std::uint8_t tick_rule() const;
    void set_tick_rule(std::uint8_t value);

    // Dummy 3: Reserved, 3 bytes
    const std::array<std::byte, 3>& dummy_3() const;
    std::array<std::byte, 3>& dummy_3();
    void set_dummy_3(const std::array<std::byte, 3>& value);

    // GatewayMessage
    GatewayMessageCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(GatewayMessageVisitor& visitor) const override;
    std::unique_ptr<GatewayMessage> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const GatewayMessage& other) const override;

    bool operator==(const RecordBodyInstrumentDefMsg& other) const;
    bool operator!=(const RecordBodyInstrumentDefMsg& other) const;

  private:
    std::optional<std::chrono::nanoseconds> ts_recv_{};
    std::optional<Decimal> min_price_increment_{};
    std::optional<Decimal> display_factor_{};
    std::optional<std::chrono::nanoseconds> expiration_{};
    std::optional<std::chrono::nanoseconds> activation_{};
    std::optional<Decimal> high_limit_price_{};
    std::optional<Decimal> low_limit_price_{};
    std::optional<Decimal> max_price_variation_{};
    std::optional<Decimal> trading_reference_price_{};
    std::optional<Decimal> unit_of_measure_qty_{};
    std::optional<Decimal> min_price_increment_amount_{};
    std::optional<Decimal> price_ratio_{};
    std::int32_t inst_attrib_value_{};
    std::uint32_t underlying_id_{};
    std::uint32_t raw_instrument_id_{};
    std::int32_t market_depth_implied_{};
    std::int32_t market_depth_{};
    std::uint32_t market_segment_id_{};
    std::uint32_t max_trade_vol_{};
    std::int32_t min_lot_size_{};
    std::int32_t min_lot_size_block_{};
    std::int32_t min_lot_size_round_lot_{};
    std::uint32_t min_trade_vol_{};
    std::array<std::byte, 4> reserved_4_{};
    std::int32_t contract_multiplier_{};
    std::int32_t decay_quantity_{};
    std::int32_t original_contract_size_{};
    std::array<std::byte, 4> second_reserved_4_{};
    std::uint16_t trading_reference_date_{};
    std::int16_t appl_id_{};
    std::uint16_t maturity_year_{};
    std::uint16_t decay_start_date_{};
    std::uint16_t channel_{};
    std::string currency_{};
    std::string settl_currency_{};
    std::string secsubtype_{};
    std::string raw_symbol_{};
    std::string group_{};
    std::string exchange_{};
    std::string asset_{};
    std::string cfi_{};
    std::string security_type_{};
    std::string unit_of_measure_{};
    std::string underlying_{};
    std::string strike_price_currency_{};
    InstrumentClass instrument_class_{};
    std::array<std::byte, 2> reserved_2_{};
    std::optional<Decimal> strike_price_{};
    std::array<std::byte, 6> reserved_6_{};
    MatchAlgorithm match_algorithm_{};
    std::uint8_t md_security_trading_status_{};
    std::uint8_t main_fraction_{};
    std::uint8_t price_display_format_{};
    std::uint8_t settl_price_type_{};
    std::uint8_t sub_fraction_{};
    std::uint8_t underlying_product_{};
    SecurityUpdateAction security_update_action_{};
    std::uint8_t maturity_month_{};
    std::uint8_t maturity_day_{};
    std::uint8_t maturity_week_{};
    UserDefinedInstrument user_defined_instrument_{};
    std::int8_t contract_multiplier_unit_{};
    std::int8_t flow_schedule_type_{};
    std::uint8_t tick_rule_{};
    std::array<std::byte, 3> dummy_3_{};
};

} // namespace databento::marketdata::normalized::dbn::v1
