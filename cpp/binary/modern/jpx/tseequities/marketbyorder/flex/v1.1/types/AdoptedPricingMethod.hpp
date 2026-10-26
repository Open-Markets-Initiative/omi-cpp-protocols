#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates the pricing method in place when the execution occurred
struct AdoptedPricingMethod {

    static constexpr auto name = "Adopted Pricing Method";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr AdoptedPricingMethod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AdoptedPricingMethod(const std::uint8_t &value)
     : value{ value } {}

    // get value of AdoptedPricingMethod field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
