#pragma once

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../enums/PriceMethod.hpp"
#include "../groups/CombinationLeg.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// The Combination Symbol Directory is a specialised reference data message used for defining
// combinations with up to 6 legs. It represents both standard combinations defined by ASX and
// user defined combinations created by participants
class CombinationSymbolDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::CombinationSymbolDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 221;

    CombinationSymbolDirectoryMessage() = default;
    CombinationSymbolDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, const std::string& symbol_name, const std::string& long_name, const std::string& cfi_code, PriceMethod price_method, std::uint8_t price_display_decimals, std::uint32_t price_fractional_denominator, std::uint32_t price_minimum_tick, std::uint8_t legs, const std::array<CombinationLeg, 6>& combination_leg);

    // Nanoseconds: Nanoseconds portion of the Nanoseconds, accurate to 1,000 nanoseconds.
    std::chrono::nanoseconds nanoseconds() const;
    void set_nanoseconds(std::chrono::nanoseconds value);

    // Trade Date: Trade Date. Represented as number of days since 1 January 1970.
    std::uint16_t trade_date() const;
    void set_trade_date(std::uint16_t value);

    // Tradeable Instrument Id: Identifier of the Order Book.
    std::uint32_t tradeable_instrument_id() const;
    void set_tradeable_instrument_id(std::uint32_t value);

    // Symbol Name: The unique tradable instrument name.
    const std::string& symbol_name() const;
    std::string& symbol_name();
    void set_symbol_name(const std::string& value);

    // Long Name: Additional instrument series information.
    const std::string& long_name() const;
    std::string& long_name();
    void set_long_name(const std::string& value);

    // Cfi Code: Indicates the type of security using ISO 10962 standard, CFI code values.
    const std::string& cfi_code() const;
    std::string& cfi_code();
    void set_cfi_code(const std::string& value);

    // Price Method: Pricing method
    PriceMethod price_method() const;
    void set_price_method(PriceMethod value);

    // Price Display Decimals: Suggested number of decimals to display the price at.
    std::uint8_t price_display_decimals() const;
    void set_price_display_decimals(std::uint8_t value);

    // Price Fractional Denominator: Denominator of the price to yield the floating point
    // price.
    std::uint32_t price_fractional_denominator() const;
    void set_price_fractional_denominator(std::uint32_t value);

    // Price Minimum Tick: Minimum tick size. Divide by the Price Fractional Denominator to
    // determine the floating point value.
    std::uint32_t price_minimum_tick() const;
    void set_price_minimum_tick(std::uint32_t value);

    // Legs: Number of legs.
    std::uint8_t legs() const;
    void set_legs(std::uint8_t value);

    // Combination Leg: Combination Leg
    const std::array<CombinationLeg, 6>& combination_leg() const;
    std::array<CombinationLeg, 6>& combination_leg();
    void set_combination_leg(const std::array<CombinationLeg, 6>& value);

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

    bool operator==(const CombinationSymbolDirectoryMessage& other) const;
    bool operator!=(const CombinationSymbolDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    std::string symbol_name_{};
    std::string long_name_{};
    std::string cfi_code_{};
    PriceMethod price_method_{};
    std::uint8_t price_display_decimals_{};
    std::uint32_t price_fractional_denominator_{};
    std::uint32_t price_minimum_tick_{};
    std::uint8_t legs_{};
    std::array<CombinationLeg, 6> combination_leg_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
