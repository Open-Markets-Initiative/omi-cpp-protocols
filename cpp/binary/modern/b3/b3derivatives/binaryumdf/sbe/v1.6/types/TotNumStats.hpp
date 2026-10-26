#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// totNumStats
struct TotNumStats {

    static constexpr const char* name = "Tot Num Stats";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr TotNumStats()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotNumStats(const std::uint16_t value)
     : value{ value } {}

    // get value of TotNumStats field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
