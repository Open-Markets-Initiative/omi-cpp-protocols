#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace siac::opra::output::obi::v6_2 {

// Represents the last price paid for an option during the trading day.
struct LastPrice {

    static constexpr const char* name = "Last Price";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LastPrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastPrice(const std::int32_t value)
     : value{ std::byteswap(value) } {}

    // get value of LastPrice field
    [[nodiscard]] std::int32_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::int32_t value;
};
}
