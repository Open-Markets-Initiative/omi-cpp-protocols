#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <string_view>

#include "../common/Decimal.hpp"
#include "../enums/ExpiryMonth.hpp"
#include "../enums/OptionType.hpp"
#include "../messages/Message.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

class Visitor;

// The Options Symbol Directory message describes options and warrants contracts.
class OptionsSymbolDirectoryMessage : public Message {
  public:
    // The code that selects this message
    static constexpr MessageCode message_type = MessageType::OptionsSymbolDirectoryMessage;
    // Bytes of this message on the wire
    static constexpr std::size_t wire_size = 219;

    OptionsSymbolDirectoryMessage() = default;
    OptionsSymbolDirectoryMessage(std::chrono::nanoseconds nanoseconds, std::uint16_t trade_date, std::uint32_t tradeable_instrument_id, const std::string& symbol_name, const std::string& long_name, const std::string& isin, const std::string& exchange, const std::string& instrument, const std::string& cfi_code, std::uint16_t expiry_year, ExpiryMonth expiry_month, OptionType option_type, Decimal strike, std::uint32_t underlying_tradeable_instrument_id, std::uint8_t price_display_decimals, std::uint32_t price_fractional_denominator, std::uint32_t price_minimum_tick, std::uint8_t strike_price_decimal_position, std::uint32_t strike_price_fractional_denominator, std::uint32_t strike_price_minimum_tick, std::uint32_t last_trading_date, Decimal prior_day_settlement, std::uint64_t volatility, const std::string& currency, std::uint64_t lot_size_or_face_value, std::uint8_t maturity_value, std::uint16_t coupon_rate, std::uint8_t payments_per_year, std::uint32_t block_lot_size, std::uint32_t expiry_date, const std::string& basis_of_quotation);

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

    // Isin: Reserved for future use.
    const std::string& isin() const;
    std::string& isin();
    void set_isin(const std::string& value);

    // Exchange: Denotes the exchange identifier of the contract
    const std::string& exchange() const;
    std::string& exchange();
    void set_exchange(const std::string& value);

    // Instrument: Denotes the instrument identifier of the contract.
    const std::string& instrument() const;
    std::string& instrument();
    void set_instrument(const std::string& value);

    // Cfi Code: Indicates the type of security using ISO 10962 standard, CFI code values.
    const std::string& cfi_code() const;
    std::string& cfi_code();
    void set_cfi_code(const std::string& value);

    // Expiry Year: Year of expiry (YYYY) for futures contract types, zero otherwise.
    std::uint16_t expiry_year() const;
    void set_expiry_year(std::uint16_t value);

    // Expiry Month: Month of expiry for futures contract types, zero otherwise.
    ExpiryMonth expiry_month() const;
    void set_expiry_month(ExpiryMonth value);

    // Option Type: Indicates the type of option
    OptionType option_type() const;
    void set_option_type(OptionType value);

    // Strike: Strike price of contract. Divide by the Strike Price Fractional Denominator to
    // determine the floating point value.
    Decimal strike() const;
    void set_strike(Decimal value);

    // Underlying Tradeable Instrument Id: Identifier of the Underlying Tradeable Instrument
    // (can be zero if underlying not defined).
    std::uint32_t underlying_tradeable_instrument_id() const;
    void set_underlying_tradeable_instrument_id(std::uint32_t value);

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

    // Strike Price Decimal Position: Number of decimals to display the strike price.
    std::uint8_t strike_price_decimal_position() const;
    void set_strike_price_decimal_position(std::uint8_t value);

    // Strike Price Fractional Denominator: Denominator of the Strike Price to yield the
    // floating point strike price.
    std::uint32_t strike_price_fractional_denominator() const;
    void set_strike_price_fractional_denominator(std::uint32_t value);

    // Strike Price Minimum Tick: Minimum tick size for the Strike Price. Divide by the Strike
    // Price Fractional Denominator to determine the floating point value.
    std::uint32_t strike_price_minimum_tick() const;
    void set_strike_price_minimum_tick(std::uint32_t value);

    // Last Trading Date: The Last Trading Day as specified in the ASX 24 Contract
    // Specifications. Reported in Unix Time (number of seconds since 00:00 1 January 1970
    // GMT). Convert to AEST/ADST as appropriate to determine the date.
    std::uint32_t last_trading_date() const;
    void set_last_trading_date(std::uint32_t value);

    // Prior Day Settlement: Prior Day Settlement price. Divide by the Price Fractional
    // Denominator to determine the floating point value.
    Decimal prior_day_settlement() const;
    void set_prior_day_settlement(Decimal value);

    // Volatility: Volatility for an option contract.
    std::uint64_t volatility() const;
    void set_volatility(std::uint64_t value);

    // Currency: Currency of contract.
    const std::string& currency() const;
    std::string& currency();
    void set_currency(const std::string& value);

    // Lot Size Or Face Value: The Contract Unit as specified in the ASX 24 Contract
    // Specifications.
    std::uint64_t lot_size_or_face_value() const;
    void set_lot_size_or_face_value(std::uint64_t value);

    // Maturity Value: The number of days or years to maturity for bills or bonds as specified
    // in the ASX 24 Contract Specifications.
    std::uint8_t maturity_value() const;
    void set_maturity_value(std::uint8_t value);

    // Coupon Rate: The coupon percentage rate for bonds.
    std::uint16_t coupon_rate() const;
    void set_coupon_rate(std::uint16_t value);

    // Payments Per Year: Number of payments per year for bonds.
    std::uint8_t payments_per_year() const;
    void set_payments_per_year(std::uint8_t value);

    // Block Lot Size: Indicates the number of lots that represent a block lot for the order
    // book.
    std::uint32_t block_lot_size() const;
    void set_block_lot_size(std::uint32_t value);

    // Expiry Date: The Settlement Date as specified in the ASX 24 Contract Specifications.
    // Reported in Unix Time (number of seconds since 00:00 1 January 1970 GMT). Convert to
    // AEST/ADST as appropriate to determine the date.
    std::uint32_t expiry_date() const;
    void set_expiry_date(std::uint32_t value);

    // Basis Of Quotation: Blank filled. Not available for ASX 24 products.
    const std::string& basis_of_quotation() const;
    std::string& basis_of_quotation();
    void set_basis_of_quotation(const std::string& value);

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

    bool operator==(const OptionsSymbolDirectoryMessage& other) const;
    bool operator!=(const OptionsSymbolDirectoryMessage& other) const;

  private:
    std::chrono::nanoseconds nanoseconds_{};
    std::uint16_t trade_date_{};
    std::uint32_t tradeable_instrument_id_{};
    std::string symbol_name_{};
    std::string long_name_{};
    std::string isin_{};
    std::string exchange_{};
    std::string instrument_{};
    std::string cfi_code_{};
    std::uint16_t expiry_year_{};
    ExpiryMonth expiry_month_{};
    OptionType option_type_{};
    Decimal strike_{ 0, -2 };
    std::uint32_t underlying_tradeable_instrument_id_{};
    std::uint8_t price_display_decimals_{};
    std::uint32_t price_fractional_denominator_{};
    std::uint32_t price_minimum_tick_{};
    std::uint8_t strike_price_decimal_position_{};
    std::uint32_t strike_price_fractional_denominator_{};
    std::uint32_t strike_price_minimum_tick_{};
    std::uint32_t last_trading_date_{};
    Decimal prior_day_settlement_{ 0, -2 };
    std::uint64_t volatility_{};
    std::string currency_{};
    std::uint64_t lot_size_or_face_value_{};
    std::uint8_t maturity_value_{};
    std::uint16_t coupon_rate_{};
    std::uint8_t payments_per_year_{};
    std::uint32_t block_lot_size_{};
    std::uint32_t expiry_date_{};
    std::string basis_of_quotation_{};
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
