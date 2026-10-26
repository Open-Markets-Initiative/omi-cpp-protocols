#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Anomalous Order Threshold price (AOT).
struct AotPrice {

    static constexpr const char* name = "Aot Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 2;
    static constexpr double denominator = 100;
    using type = std::int64_t;

    // default constructor
    constexpr AotPrice()
     : value{ 0 } {}

    // constructor for AotPrice field
    constexpr explicit AotPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of AotPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of AotPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
