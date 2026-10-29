#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Max Strike Price
class MaxStrikePrice {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    MaxStrikePrice() = default;
    MaxStrikePrice(std::int8_t max_strike_price_exponent, std::int32_t max_strike_price_mantissa);

    // Max Strike Price Exponent: The maximum allowable strike price.
    std::int8_t max_strike_price_exponent() const;
    void set_max_strike_price_exponent(std::int8_t value);

    // Max Strike Price Mantissa: The maximum allowable strike price.
    std::int32_t max_strike_price_mantissa() const;
    void set_max_strike_price_mantissa(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const MaxStrikePrice& other) const;
    bool operator!=(const MaxStrikePrice& other) const;

  private:
    std::int8_t max_strike_price_exponent_{};
    std::int32_t max_strike_price_mantissa_{};
};

std::ostream& operator<<(std::ostream& out, const MaxStrikePrice& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
