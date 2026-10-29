#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

// Lower boundary for the Indicative Match Price.
struct LowerCollar {

    static constexpr const char* name = "Lower Collar";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr LowerCollar()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LowerCollar(const std::int32_t value)
     : value{ value } {}

    // get value of LowerCollar field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
