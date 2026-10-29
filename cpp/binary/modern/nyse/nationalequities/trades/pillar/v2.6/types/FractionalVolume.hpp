#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// The volume of the trade in shares, inclusive of any fractional quantity. Implied scale is 6.
struct FractionalVolume {

    static constexpr const char* name = "Fractional Volume";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr FractionalVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FractionalVolume(const std::uint64_t value)
     : value{ value } {}

    // get value of FractionalVolume field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
