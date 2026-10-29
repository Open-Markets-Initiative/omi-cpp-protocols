#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// The exchange cumulative volume for the stock throughout the day.
struct TotalVolume {

    static constexpr const char* name = "Total Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of TotalVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
