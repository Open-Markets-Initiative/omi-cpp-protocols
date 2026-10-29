#pragma once

#include <cstddef>
#include <cstdint>

namespace bse::bseindia::eobi::fbe::v1_4 {


// Indicates if product is in the state Fast Market.
struct FastMarketIndicator {

    static constexpr auto name = "Fast Market Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr FastMarketIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FastMarketIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of FastMarketIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
