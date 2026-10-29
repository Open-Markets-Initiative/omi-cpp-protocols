#pragma once

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

// Premium Break Point
class PremiumBreakPoint {
  public:
    // Bytes of this struct on the wire
    static constexpr std::size_t wire_size = 5;

    PremiumBreakPoint() = default;
    PremiumBreakPoint(std::int8_t premium_break_point_exponent, std::int32_t premium_break_point_mantissa);

    // Premium Break Point Exponent: The premium price where above and below fractions take
    // effect.
    std::int8_t premium_break_point_exponent() const;
    void set_premium_break_point_exponent(std::int8_t value);

    // Premium Break Point Mantissa: The premium price where above and below fractions take
    // effect.
    std::int32_t premium_break_point_mantissa() const;
    void set_premium_break_point_mantissa(std::int32_t value);

    // Read this from the bytes at data, and return how many were consumed; throws DecodeError when too few
    std::size_t decode(const std::byte* data, std::size_t length);
    // Write this to the bytes at data, and return how many were written; throws EncodeError when too few
    std::size_t encode(std::byte* data, std::size_t capacity) const;
    // How many bytes encode would write
    std::size_t encoded_size() const;
    void print(std::ostream& out) const;

    bool operator==(const PremiumBreakPoint& other) const;
    bool operator!=(const PremiumBreakPoint& other) const;

  private:
    std::int8_t premium_break_point_exponent_{};
    std::int32_t premium_break_point_mantissa_{};
};

std::ostream& operator<<(std::ostream& out, const PremiumBreakPoint& value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
