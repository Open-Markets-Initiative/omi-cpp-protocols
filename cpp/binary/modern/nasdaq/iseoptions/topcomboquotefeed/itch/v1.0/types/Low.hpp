// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0: types/Low.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Low price for the day.
struct Low {

    static constexpr const char* name = "Low";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr Low()
     : value{ 0 } {}

    // constructor for Low field
    constexpr explicit Low(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of Low field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of Low field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
