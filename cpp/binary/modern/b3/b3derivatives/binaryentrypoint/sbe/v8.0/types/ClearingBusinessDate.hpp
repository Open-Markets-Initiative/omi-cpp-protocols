#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// clearingBusinessDate
struct ClearingBusinessDate {

    static constexpr const char* name = "Clearing Business Date";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr ClearingBusinessDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClearingBusinessDate(const std::uint16_t value)
     : value{ value } {}

    // get value of ClearingBusinessDate field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
