#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Minimum Below Premium Fraction
class MinimumBelowPremiumFraction {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    MinimumBelowPremiumFraction() = default;
    MinimumBelowPremiumFraction(std::int8_t minimum_below_premium_fraction_exponent, std::int32_t minimum_below_premium_fraction_mantissa);

    // Minimum Below Premium Fraction Exponent: The multiple that premium can be when below the
    // break point.
    std::int8_t minimum_below_premium_fraction_exponent() const;
    void set_minimum_below_premium_fraction_exponent(std::int8_t value);

    // Minimum Below Premium Fraction Mantissa: The multiple that premium can be when below the
    // break point.
    std::int32_t minimum_below_premium_fraction_mantissa() const;
    void set_minimum_below_premium_fraction_mantissa(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MinimumBelowPremiumFraction& other) const;
    bool operator!=(const MinimumBelowPremiumFraction& other) const;

  private:
    std::int8_t minimum_below_premium_fraction_exponent_{};
    std::int32_t minimum_below_premium_fraction_mantissa_{};
};

std::ostream& operator<<(std::ostream& out, const MinimumBelowPremiumFraction& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
