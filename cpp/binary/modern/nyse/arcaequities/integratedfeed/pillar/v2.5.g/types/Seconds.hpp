#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// Seconds since Jan 1, 1970 00:00:00 UTC
struct Seconds {

    static constexpr const char* name = "Seconds";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Seconds()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Seconds(const std::uint32_t value)
     : value{ value } {}

    // get value of Seconds field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
