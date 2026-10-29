#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// The Quantity Of Shares For An Order Or Trade
struct Volume {

    static constexpr const char* name = "Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr Volume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Volume(const std::uint32_t value)
     : value{ value } {}

    // get value of Volume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
