#pragma once

#include <cstddef>
#include <cstdint>

namespace eurex::t7::eobi::fbe::v15_0 {

// 
struct QuantityScalingFactor {

    static constexpr const char* name = "Quantity Scaling Factor";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type no_value = 0xFFFF;
static const type maximum_value = 1000;
static const type minimum_value = 1;

    // default constructor
    constexpr QuantityScalingFactor()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit QuantityScalingFactor(const std::uint16_t value)
     : value{ value } {}

    // get value of QuantityScalingFactor field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
