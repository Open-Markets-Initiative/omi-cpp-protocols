// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0: types/High.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// High price for the day.
struct High {

    static constexpr const char* name = "High";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr High()
     : value{ 0 } {}

    // constructor for High field
    constexpr explicit High(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of High field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of High field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
