#pragma once

#include <bit>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// Represents the price of the underlying security.
struct UnderlyingPrice {

    static constexpr const char* name = "Underlying Price";
    static constexpr std::size_t size =  8;
    using type = std::int64_t;

    // default constructor
    constexpr UnderlyingPrice()
     : value{ 0 } {}

    // constructor for UnderlyingPrice field
    constexpr explicit UnderlyingPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of UnderlyingPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // the exponent underlyingpricedenominatorcode states, or 0 for a code it does not state
    [[nodiscard]] static constexpr int exponent(const char code) {
        switch (code) {
            case 'A': return -1;
            case 'B': return -2;
            case 'C': return -3;
            case 'D': return -4;
            case 'E': return -5;
            case 'F': return -6;
            case 'G': return -7;
            case 'H': return -8;
            case 'I': return 0;
            default: return 0;
        }
    }

    // a code states an exponent, so this always reads as a decimal and never as a fraction.
    // Both predicates are here, and mean the same as they do on a fraction, so a caller can ask
    // either type the same question.
    [[nodiscard]] static constexpr bool is_decimal(const char) {
        return true;
    }

    [[nodiscard]] static constexpr bool is_fraction(const char) {
        return false;
    }

    // does underlyingpricedenominatorcode state this code? Where it does not, exponent() falls back to zero and the
    // mantissa reads unscaled, so a caller that needs to say so asks this and reports the code
    // it was handed rather than presenting a price the venue did not state
    [[nodiscard]] static constexpr bool is_stated(const char code) {
        switch (code) {
            case 'A': return true;
            case 'B': return true;
            case 'C': return true;
            case 'D': return true;
            case 'E': return true;
            case 'F': return true;
            case 'G': return true;
            case 'H': return true;
            case 'I': return true;
            default: return false;
        }
    }

    // decimal value of UnderlyingPrice field, scaled by the code underlyingpricedenominatorcode states
    [[nodiscard]] double get(const char code) const {
        return static_cast<double>(integer()) * std::pow(10.0, static_cast<double>(exponent(code)));
    }

  protected:
    std::int64_t value;
};
}
