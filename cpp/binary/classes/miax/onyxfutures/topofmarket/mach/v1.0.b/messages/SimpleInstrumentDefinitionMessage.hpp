#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/Currency.hpp"
#include "../enums/Exchange.hpp"
#include "../enums/InstrumentIdSource.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/MatchAlgorithm.hpp"
#include "../enums/SettlementCurrency.hpp"
#include "../enums/SettlementPriceTypeCalcMethod.hpp"
#include "../enums/TradingCollarVariationType.hpp"
#include "../enums/UnderlyingAssetType.hpp"
#include "../enums/UnitOfMeasure.hpp"
#include "../messages/Data.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class DataVisitor;

// used to disseminate all Simple Instruments traded on MIAX FuturesOnyx for the current
// trading session
class SimpleInstrumentDefinitionMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::SimpleInstrumentDefinitionMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 119;

    SimpleInstrumentDefinitionMessage() = default;
    SimpleInstrumentDefinitionMessage(std::chrono::nanoseconds timestamp, std::uint32_t instrument_id, UnderlyingAssetType underlying_asset_type, const std::string& underlying_asset, const std::string& product_group_code, const std::string& exchange, InstrumentIdSource instrument_id_source, InstrumentType instrument_type, std::uint32_t maturity_month_year, Currency currency, SettlementCurrency settlement_currency, MatchAlgorithm match_algorithm, std::uint32_t minimum_size, std::uint32_t maximum_size, Decimal tick, const std::string& unit_of_measure, std::uint32_t unit_of_measure_quantity, Decimal settlement_price, SettlementPriceTypeCalcMethod settlement_price_type_calc_method, std::uint32_t total_volume, std::uint32_t open_interest_quantity, Decimal high_limit_price, Decimal low_limit_price, TradingCollarVariationType trading_collar_variation_type, Decimal trading_collar_variation, const std::array<std::byte, 16>& reserved_16);

    // Timestamp: Matching Engine time
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Instrument Id: Unique ID assigned by MIAX Futures Onyx
    std::uint32_t instrument_id() const;
    void set_instrument_id(std::uint32_t value);

    // Underlying Asset Type: Underlying Asset Type of this instrument
    UnderlyingAssetType underlying_asset_type() const;
    void set_underlying_asset_type(UnderlyingAssetType value);

    // Underlying Asset: Underlying Asset Code
    const std::string& underlying_asset() const;
    std::string& underlying_asset();
    void set_underlying_asset(const std::string& value);

    // Product Group Code: Product Group Code
    const std::string& product_group_code() const;
    std::string& product_group_code();
    void set_product_group_code(const std::string& value);

    // Exchange: Exchange
    const std::string& exchange() const;
    std::string& exchange();
    void set_exchange(const std::string& value);

    // Instrument Id Source: Indicates whether the Instrument ID has been assigned by the
    // exchange or from an external industry source
    InstrumentIdSource instrument_id_source() const;
    void set_instrument_id_source(InstrumentIdSource value);

    // Instrument Type: ‘F’ = Futures
    InstrumentType instrument_type() const;
    void set_instrument_type(InstrumentType value);

    // Maturity Month Year: Maturity Month-Year is the expiration date of a Simple Instrument
    std::uint32_t maturity_month_year() const;
    void set_maturity_month_year(std::uint32_t value);

    // Currency: The currency in which all Futures Instruments of the Futures Product will
    // trade
    Currency currency() const;
    void set_currency(Currency value);

    // Settlement Currency: The Currency in which the Product settles
    SettlementCurrency settlement_currency() const;
    void set_settlement_currency(SettlementCurrency value);

    // Match Algorithm: The allocation model used by the MIAX Futures Onyx Trading Platform for
    // the Product
    MatchAlgorithm match_algorithm() const;
    void set_match_algorithm(MatchAlgorithm value);

    // Minimum Size: Minimum Order Size
    std::uint32_t minimum_size() const;
    void set_minimum_size(std::uint32_t value);

    // Maximum Size: Maximum Order Size
    std::uint32_t maximum_size() const;
    void set_maximum_size(std::uint32_t value);

    // Tick: Order Entry Price Tick of the Product
    Decimal tick() const;
    void set_tick(Decimal value);

    // Unit Of Measure: Individual unit of the Deliverable of the Underlying Asset associated
    // with the Futures Contract
    const std::string& unit_of_measure() const;
    std::string& unit_of_measure();
    void set_unit_of_measure(const std::string& value);

    // Unit Of Measure Quantity: The quantity of the Underlying Asset that is required for the
    // Deliverable associated with the Futures Contract
    std::uint32_t unit_of_measure_quantity() const;
    void set_unit_of_measure_quantity(std::uint32_t value);

    // Settlement Price: The previous day’s Settlement Price
    Decimal settlement_price() const;
    void set_settlement_price(Decimal value);

    // Settlement Price Type Calc Method: Actual or Theoretical Settlement Price Indicator
    SettlementPriceTypeCalcMethod settlement_price_type_calc_method() const;
    void set_settlement_price_type_calc_method(SettlementPriceTypeCalcMethod value);

    // Total Volume: The aggregate amount of volume that has traded from the prior Trading Day
    std::uint32_t total_volume() const;
    void set_total_volume(std::uint32_t value);

    // Open Interest Quantity: The amount of aggregate open contracts in a Simple Instrument
    std::uint32_t open_interest_quantity() const;
    void set_open_interest_quantity(std::uint32_t value);

    // High Limit Price: The Upper Band of the Daily Trading Limit of a Futures Product
    Decimal high_limit_price() const;
    void set_high_limit_price(Decimal value);

    // Low Limit Price: The Lower Band of the Daily Trading Limit of a Futures Product
    Decimal low_limit_price() const;
    void set_low_limit_price(Decimal value);

    // Trading Collar Variation Type: Trading Collar Variation Type
    TradingCollarVariationType trading_collar_variation_type() const;
    void set_trading_collar_variation_type(TradingCollarVariationType value);

    // Trading Collar Variation: The Dollar Value or Percentage Value used in the calculation
    // of theTrading Collar
    Decimal trading_collar_variation() const;
    void set_trading_collar_variation(Decimal value);

    // Reserved 16: Reserved for future use
    const std::array<std::byte, 16>& reserved_16() const;
    std::array<std::byte, 16>& reserved_16();
    void set_reserved_16(const std::array<std::byte, 16>& value);

    // Data
    DataCode type() const override;
    std::string_view name() const override;
    std::size_t decode(const std::byte* data, std::size_t length) override;
    std::size_t encode(std::byte* data, std::size_t capacity) const override;
    std::size_t encoded_size() const override;
    void accept(DataVisitor& visitor) const override;
    std::unique_ptr<Data> clone() const override;
    void print(std::ostream& out) const override;
    bool equals(const Data& other) const override;

    bool operator==(const SimpleInstrumentDefinitionMessage& other) const;
    bool operator!=(const SimpleInstrumentDefinitionMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t instrument_id_{};
    UnderlyingAssetType underlying_asset_type_{};
    std::string underlying_asset_{};
    std::string product_group_code_{};
    std::string exchange_{};
    InstrumentIdSource instrument_id_source_{};
    InstrumentType instrument_type_{};
    std::uint32_t maturity_month_year_{};
    Currency currency_{};
    SettlementCurrency settlement_currency_{};
    MatchAlgorithm match_algorithm_{};
    std::uint32_t minimum_size_{};
    std::uint32_t maximum_size_{};
    Decimal tick_{ 0, -9 };
    std::string unit_of_measure_{};
    std::uint32_t unit_of_measure_quantity_{};
    Decimal settlement_price_{ 0, -9 };
    SettlementPriceTypeCalcMethod settlement_price_type_calc_method_{};
    std::uint32_t total_volume_{};
    std::uint32_t open_interest_quantity_{};
    Decimal high_limit_price_{ 0, -9 };
    Decimal low_limit_price_{ 0, -9 };
    TradingCollarVariationType trading_collar_variation_type_{};
    Decimal trading_collar_variation_{ 0, -9 };
    std::array<std::byte, 16> reserved_16_{};
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
