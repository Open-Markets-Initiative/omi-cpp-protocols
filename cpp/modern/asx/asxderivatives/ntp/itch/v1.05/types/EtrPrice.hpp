#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Extreme Trade Range price (ETR), if zero, then MIR is not enforced.
struct EtrPrice {

    static constexpr const char* name = "Etr Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr EtrPrice()
     : value{ 0 } {}

    // constructor for EtrPrice field
    constexpr explicit EtrPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of EtrPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of EtrPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
