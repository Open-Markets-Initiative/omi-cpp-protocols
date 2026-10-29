#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Nanosecond offset from last
struct Timestamp {

    static constexpr const char* name = "Timestamp";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Timestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Timestamp(const std::uint32_t value)
     : value{ value } {}

    // get value of Timestamp field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
