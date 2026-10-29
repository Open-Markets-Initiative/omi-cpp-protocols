#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Minimum Strike Price Fraction
class MinimumStrikePriceFraction {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    MinimumStrikePriceFraction() = default;
    MinimumStrikePriceFraction(std::int8_t minimum_strike_price_fraction_exponent, std::int32_t minimum_strike_price_fraction_mantissa);

    // Minimum Strike Price Fraction Exponent: The multiple by which the strike price can be
    std::int8_t minimum_strike_price_fraction_exponent() const;
    void set_minimum_strike_price_fraction_exponent(std::int8_t value);

    // Minimum Strike Price Fraction Mantissa: The multiple by which the strike price can be
    std::int32_t minimum_strike_price_fraction_mantissa() const;
    void set_minimum_strike_price_fraction_mantissa(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MinimumStrikePriceFraction& other) const;
    bool operator!=(const MinimumStrikePriceFraction& other) const;

  private:
    std::int8_t minimum_strike_price_fraction_exponent_{};
    std::int32_t minimum_strike_price_fraction_mantissa_{};
};

std::ostream& operator<<(std::ostream& out, const MinimumStrikePriceFraction& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
