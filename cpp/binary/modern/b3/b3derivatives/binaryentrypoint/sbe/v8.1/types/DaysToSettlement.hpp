#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// daysToSettlement
struct DaysToSettlement {

    static constexpr const char* name = "Days To Settlement";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr DaysToSettlement()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit DaysToSettlement(const std::uint16_t value)
     : value{ value } {}

    // get value of DaysToSettlement field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
