#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// totNumBids
struct TotNumBids {

    static constexpr const char* name = "Tot Num Bids";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotNumBids()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNumBids(const std::uint32_t value)
     : value{ value } {}

    // get value of TotNumBids field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
