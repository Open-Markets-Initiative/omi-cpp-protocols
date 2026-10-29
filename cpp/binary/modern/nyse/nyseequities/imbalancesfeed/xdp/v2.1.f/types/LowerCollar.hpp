#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// If the IndicativeMatchPrice is not strictly between the UpperCollar and the LowerCollar, special auction rules apply.
struct LowerCollar {

    static constexpr const char* name = "Lower Collar";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LowerCollar()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LowerCollar(const std::uint32_t value)
     : value{ value } {}

    // get value of LowerCollar field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
