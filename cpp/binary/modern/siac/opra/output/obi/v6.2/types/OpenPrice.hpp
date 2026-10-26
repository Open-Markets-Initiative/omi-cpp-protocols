#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// Represents the first price paid for an option during the trading day.
struct OpenPrice {

    static constexpr const char* name = "Open Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr OpenPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenPrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of OpenPrice field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
