#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {


// 
struct HhiIndicator {

    static constexpr auto name = "Hhi Indicator";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 0x80;
static const type maximum_value = 100;
static const type minimum_value = -1;

    // default constructor
    constexpr HhiIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HhiIndicator(const std::int8_t &value)
     : value{ value } {}

    // get value of HhiIndicator field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
