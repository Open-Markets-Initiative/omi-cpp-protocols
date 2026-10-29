#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v3_0 {


// 
struct ImpliedMarketIndicator {

    static constexpr auto name = "Implied Market Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 3;
static const type minimum_value = 0;

    // default constructor
    constexpr ImpliedMarketIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImpliedMarketIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of ImpliedMarketIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
