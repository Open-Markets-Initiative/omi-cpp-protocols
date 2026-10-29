#pragma once

#include <cstddef>
#include <cstdint>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Cumulative number of shares executed
struct Shares {

    static constexpr const char* name = "Shares";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Shares()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Shares(const std::uint32_t value)
     : value{ value } {}

    // get value of Shares field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
