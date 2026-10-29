#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

#include "../common/Decimal.hpp"
#include "../enums/Currency.hpp"
#include "../enums/Exchange.hpp"
#include "../enums/InstrumentIdSource.hpp"
#include "../enums/InstrumentType.hpp"
#include "../enums/MatchAlgorithm.hpp"
#include "../enums/SettlementCurrency.hpp"
#include "../enums/TradingCollarVariationType.hpp"
#include "../enums/UnderlyingAssetType.hpp"
#include "../enums/UnitOfMeasure.hpp"
#include "../groups/InstrumentLeg.hpp"
#include "../messages/Data.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class DataVisitor;

// Used to disseminate all Complex Instruments traded on MIAX Futures Onyx for the current
// trading session
class ComplexInstrumentDefinitionMessage : public Data {
  public:
    // The code that selects this message
    static constexpr DataCode message_type = MessageType::ComplexInstrumentDefinitionMessage;

    ComplexInstrumentDefinitionMessage() = default;
    ComplexInstrumentDefinitionMessage(std::chrono::nanoseconds timestamp, std::uint32_t strategy_id, UnderlyingAssetType underlying_asset_type, const std::string& underlying_asset, const std::string& product_group_code, char spread_type, const std::string& exchange, InstrumentIdSource instrument_id_source, InstrumentType instrument_type, Currency currency, SettlementCurrency settlement_currency, MatchAlgorithm match_algorithm, std::uint32_t minimum_size, std::uint32_t maximum_size, Decimal tick, const std::string& unit_of_measure, std::uint32_t unit_of_measure_quantity, TradingCollarVariationType trading_collar_variation_type, Decimal trading_collar_variation, const std::array<std::byte, 16>& reserved_16, std::uint8_t number_of_legs, const std::vector<InstrumentLeg>& instrument_leg);

    // Timestamp: Matching Engine time
    std::chrono::nanoseconds timestamp() const;
    void set_timestamp(std::chrono::nanoseconds value);

    // Strategy Id: Unique ID assigned by MIAX Futures Onyx for a Complex instrument and is
    // permanent for the life of an instrument
    std::uint32_t strategy_id() const;
    void set_strategy_id(std::uint32_t value);

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

    // Spread Type: Spread Type
    char spread_type() const;
    void set_spread_type(char value);

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

    // Number Of Legs: Number of strategy legs
    std::uint8_t number_of_legs() const;
    void set_number_of_legs(std::uint8_t value);

    // Instrument Leg: Complex Strategy Number of Legs
    const std::vector<InstrumentLeg>& instrument_leg() const;
    std::vector<InstrumentLeg>& instrument_leg();
    void set_instrument_leg(const std::vector<InstrumentLeg>& value);

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

    bool operator==(const ComplexInstrumentDefinitionMessage& other) const;
    bool operator!=(const ComplexInstrumentDefinitionMessage& other) const;

  private:
    std::chrono::nanoseconds timestamp_{};
    std::uint32_t strategy_id_{};
    UnderlyingAssetType underlying_asset_type_{};
    std::string underlying_asset_{};
    std::string product_group_code_{};
    char spread_type_{};
    std::string exchange_{};
    InstrumentIdSource instrument_id_source_{};
    InstrumentType instrument_type_{};
    Currency currency_{};
    SettlementCurrency settlement_currency_{};
    MatchAlgorithm match_algorithm_{};
    std::uint32_t minimum_size_{};
    std::uint32_t maximum_size_{};
    Decimal tick_{ 0, -9 };
    std::string unit_of_measure_{};
    std::uint32_t unit_of_measure_quantity_{};
    TradingCollarVariationType trading_collar_variation_type_{};
    Decimal trading_collar_variation_{ 0, -9 };
    std::array<std::byte, 16> reserved_16_{};
    std::uint8_t number_of_legs_{};
    std::vector<InstrumentLeg> instrument_leg_{};
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
