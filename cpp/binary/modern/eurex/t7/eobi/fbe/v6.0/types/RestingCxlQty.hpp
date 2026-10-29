#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v6_0 {

// 
struct RestingCxlQty {

    static constexpr const char* name = "Resting Cxl Qty";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 0x80000000;
static const type maximum_value = 2147483647;
static const type minimum_value = -2147483647;

    // default constructor
    constexpr RestingCxlQty()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RestingCxlQty(const std::int32_t value)
     : value{ value } {}

    // get value of RestingCxlQty field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
