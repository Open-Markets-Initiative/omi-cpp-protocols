#pragma once

#include <cstddef>
#include <cstdint>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Order book the status applies to.
struct OrderBookType {

    static constexpr auto name = "Order Book Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr OrderBookType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrderBookType(const std::uint8_t &value)
     : value{ value } {}

    // get value of OrderBookType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
