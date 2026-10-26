#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Upper range of the ETR.
struct EtrUpperPrice {

    static constexpr const char* name = "Etr Upper Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr EtrUpperPrice()
     : value{ 0 } {}

    // constructor for EtrUpperPrice field
    constexpr explicit EtrUpperPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of EtrUpperPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of EtrUpperPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
