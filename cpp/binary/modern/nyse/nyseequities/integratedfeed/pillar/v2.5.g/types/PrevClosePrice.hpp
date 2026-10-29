#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

// The previous day's closing price for this security.
struct PrevClosePrice {

    static constexpr const char* name = "Prev Close Price";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PrevClosePrice()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrevClosePrice(const std::uint32_t value)
     : value{ value } {}

    // get value of PrevClosePrice field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
