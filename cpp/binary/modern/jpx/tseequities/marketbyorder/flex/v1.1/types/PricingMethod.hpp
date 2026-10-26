#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates method of pricing or status of quote display after the tag is delivered
struct PricingMethod {

    static constexpr auto name = "Pricing Method";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr PricingMethod()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PricingMethod(const std::uint8_t &value)
     : value{ value } {}

    // get value of PricingMethod field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
