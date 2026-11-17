// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0: types/First.hpp
#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Opening price for the day
struct First {

    static constexpr const char* name = "First";
    static constexpr std::size_t size =  8;
    static constexpr std::size_t precision = 8;
    static constexpr double denominator = 100000000;
    using type = std::int64_t;

    // default constructor
    constexpr First()
     : value{ 0 } {}

    // constructor for First field
    constexpr explicit First(const std::int64_t value)
     : value{ std::byteswap(value) } {}

    // get underlying integer of First field
    [[nodiscard]] std::int64_t integer() const {
        return std::byteswap(value);
    }

    // decimal value of First field
    [[nodiscard]] double get() const {
        return integer() / denominator;
    }

  protected:
    std::int64_t value;
};
}
