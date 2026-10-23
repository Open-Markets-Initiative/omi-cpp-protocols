#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {


// 
struct InputSource {

    static constexpr auto name = "Input Source";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0xFF;
static const type maximum_value = 1;
static const type minimum_value = 1;

    // default constructor
    constexpr InputSource()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InputSource(const std::uint8_t &value)
     : value{ value } {}

    // get value of InputSource field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
