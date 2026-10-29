#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Heartbeat interval in milliseconds (1 to 65536).
struct HbInterval {

    static constexpr const char* name = "Hb Interval";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr HbInterval()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HbInterval(const std::uint16_t value)
     : value{ value } {}

    // get value of HbInterval field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
