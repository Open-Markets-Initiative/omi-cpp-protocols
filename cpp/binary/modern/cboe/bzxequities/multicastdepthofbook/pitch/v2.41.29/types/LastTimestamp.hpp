#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_41_29 {

// Nanosecond offset from last unit timestamp
struct LastTimestamp {

    static constexpr const char* name = "Last Timestamp";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr LastTimestamp()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LastTimestamp(const std::uint32_t value)
     : value{ value } {}

    // get value of LastTimestamp field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
