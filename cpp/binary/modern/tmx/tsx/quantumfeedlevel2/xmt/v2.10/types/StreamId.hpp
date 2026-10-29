#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Stream Id per Source Id of the Business message
struct StreamId {

    static constexpr const char* name = "Stream Id";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr StreamId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StreamId(const std::uint16_t value)
     : value{ value } {}

    // get value of StreamId field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
