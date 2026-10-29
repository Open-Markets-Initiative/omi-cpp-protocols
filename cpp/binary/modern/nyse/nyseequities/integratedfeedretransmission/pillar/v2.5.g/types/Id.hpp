#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// ID of the originating Matching Engine partition to which this message applies.
struct Id {

    static constexpr const char* name = "Id";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Id()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Id(const std::uint32_t value)
     : value{ value } {}

    // get value of Id field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
