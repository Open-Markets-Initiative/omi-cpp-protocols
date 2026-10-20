#pragma once

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <string>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// A number with an implied scale: the wire integer (the mantissa) times ten to the
// exponent. A price of 141.5000 with a scale of -4 is Decimal(1415000, -4). The
// mantissa is what goes back on the wire, so a decoded value encodes exactly;
// to_double() is for arithmetic and display.
class Decimal {
  public:
    constexpr Decimal() = default;

    constexpr Decimal(std::int64_t mantissa, int exponent)
      : mantissa_(mantissa), exponent_(exponent) {}

    // The nearest representable value at the exponent
    static Decimal from_double(double value, int exponent) {
        return Decimal(std::llround(value / std::pow(10.0, exponent)), exponent);
    }

    constexpr std::int64_t mantissa() const { return mantissa_; }
    constexpr int exponent() const { return exponent_; }

    double to_double() const {
        return static_cast<double>(mantissa_) * std::pow(10.0, exponent_);
    }

    // Two decimals are equal when they are the same number, whatever their scales
    bool operator==(const Decimal& other) const { return compare(other) == 0; }
    bool operator!=(const Decimal& other) const { return compare(other) != 0; }
    bool operator<(const Decimal& other) const { return compare(other) < 0; }
    bool operator<=(const Decimal& other) const { return compare(other) <= 0; }
    bool operator>(const Decimal& other) const { return compare(other) > 0; }
    bool operator>=(const Decimal& other) const { return compare(other) >= 0; }

    // The exact digits: a sign, the integer part, and one digit per negative power
    std::string to_string() const {
        if (exponent_ >= 0) {
            return std::to_string(mantissa_) + std::string(static_cast<std::size_t>(exponent_), '0');
        }

        const std::size_t places = static_cast<std::size_t>(-exponent_);
        const bool negative = mantissa_ < 0;
        const std::uint64_t magnitude = negative
            ? static_cast<std::uint64_t>(-(mantissa_ + 1)) + 1
            : static_cast<std::uint64_t>(mantissa_);
        std::string digits = std::to_string(magnitude);

        if (digits.size() <= places) {
            digits.insert(0, places + 1 - digits.size(), '0');
        }

        digits.insert(digits.size() - places, 1, '.');

        return negative ? "-" + digits : digits;
    }

  private:
    __extension__ typedef __int128 wide;

    // Compare at the finer of the two scales, widening so no digits are lost
    int compare(const Decimal& other) const {
        const int exponent = exponent_ < other.exponent_ ? exponent_ : other.exponent_;
        const wide left = static_cast<wide>(mantissa_) * power(exponent_ - exponent);
        const wide right = static_cast<wide>(other.mantissa_) * power(other.exponent_ - exponent);

        return left < right ? -1 : left > right ? 1 : 0;
    }

    static wide power(int exponent) {
        wide result = 1;
        for (int index = 0; index < exponent; ++index) { result *= 10; }
        return result;
    }

    std::int64_t mantissa_ = 0;
    int exponent_ = 0;
};

inline std::ostream& operator<<(std::ostream& out, const Decimal& value) {
    return out << value.to_string();
}

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
