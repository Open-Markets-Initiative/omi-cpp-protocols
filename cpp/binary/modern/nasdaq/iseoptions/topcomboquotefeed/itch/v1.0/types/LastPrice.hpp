#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Most recent price.
struct LastPrice {

    static constexpr const char* name = "Last Price";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr LastPrice()
     : value{ 0 } {}

    // constructor for LastPrice field
    constexpr explicit LastPrice(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of LastPrice field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of LastPrice field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
