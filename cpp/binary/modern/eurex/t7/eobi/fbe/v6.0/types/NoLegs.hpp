#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v6_0 {


// 
struct NoLegs {

    static constexpr auto name = "No Legs";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 20;
static const type minimum_value = 2;

    // default constructor
    constexpr NoLegs()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NoLegs(const std::uint8_t &value)
     : value{ value } {}

    // get value of NoLegs field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
