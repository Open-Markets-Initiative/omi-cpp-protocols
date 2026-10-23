#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {

// 
struct NumberOfSellOrders {

    static constexpr const char* name = "Number Of Sell Orders";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0xFFFF;
static const type maximum_value = 65534;
static const type minimum_value = 0;

    // default constructor
    constexpr NumberOfSellOrders()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumberOfSellOrders(const std::uint16_t value)
     : value{ value } {}

    // get value of NumberOfSellOrders field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
