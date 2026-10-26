#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v13_0 {


// 
struct PrevPriceHhiIndicator {

    static constexpr auto name = "Prev Price Hhi Indicator";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 0x80;
static const type maximum_value = 100;
static const type minimum_value = -1;

    // default constructor
    constexpr PrevPriceHhiIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrevPriceHhiIndicator(const std::int8_t &value)
     : value{ value } {}

    // get value of PrevPriceHhiIndicator field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
