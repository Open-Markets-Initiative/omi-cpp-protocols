#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {

// 
struct LegRatioMultiplier {

    static constexpr const char* name = "Leg Ratio Multiplier";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0xFFFFFFFF;
static const type maximum_value = 2147483647;
static const type minimum_value = 1;

    // default constructor
    constexpr LegRatioMultiplier()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LegRatioMultiplier(const std::uint32_t value)
     : value{ value } {}

    // get value of LegRatioMultiplier field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
