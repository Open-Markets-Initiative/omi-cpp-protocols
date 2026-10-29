#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// The current refresh packet in the update
struct CurrentRefreshPkt {

    static constexpr const char* name = "Current Refresh Pkt";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr CurrentRefreshPkt()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CurrentRefreshPkt(const std::uint16_t value)
     : value{ value } {}

    // get value of CurrentRefreshPkt field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
