#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {

// 
struct NumberOfSellSides {

    static constexpr const char* name = "Number Of Sell Sides";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0xFFFF;
static const type maximum_value = 65534;
static const type minimum_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr NumberOfSellSides()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit NumberOfSellSides(const std::uint16_t value)
     : value{ value } {}

    // get value of NumberOfSellSides field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
