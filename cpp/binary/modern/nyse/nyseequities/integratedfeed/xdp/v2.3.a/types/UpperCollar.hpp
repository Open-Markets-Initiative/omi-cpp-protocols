#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// If the IndicativeMatchPrice is not strictly between the UpperCollar and the LowerCollar, special auction rules apply. See Rule 7.35P for details.
struct UpperCollar {

    static constexpr const char* name = "Upper Collar";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr UpperCollar()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UpperCollar(const std::uint32_t value)
     : value{ value } {}

    // get value of UpperCollar field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
