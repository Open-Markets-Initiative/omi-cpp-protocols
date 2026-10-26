#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Lower range of the ETR.
struct EtrLowerPrice {

    static constexpr const char* name = "Etr Lower Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr EtrLowerPrice()
     : value{ 0 } {}

    // constructor for EtrLowerPrice field
    constexpr explicit EtrLowerPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of EtrLowerPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of EtrLowerPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
