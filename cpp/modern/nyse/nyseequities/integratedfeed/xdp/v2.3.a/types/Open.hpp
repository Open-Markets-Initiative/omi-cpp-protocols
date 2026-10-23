#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// The exchange Opening price of this stock for the day. Use the Price Scale in the symbol index msg.
struct Open {

    static constexpr const char* name = "Open";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Open()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Open(const std::uint32_t value)
     : value{ value } {}

    // get value of Open field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
