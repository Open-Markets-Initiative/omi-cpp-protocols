#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Upper range of the AOT.
struct AotUpperPrice {

    static constexpr const char* name = "Aot Upper Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr AotUpperPrice()
     : value{ 0 } {}

    // constructor for AotUpperPrice field
    constexpr explicit AotUpperPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AotUpperPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AotUpperPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
