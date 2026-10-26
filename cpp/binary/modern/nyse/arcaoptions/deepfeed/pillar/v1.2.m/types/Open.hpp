#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The First price of the series for the day. Use the Price scale from the series index mapping.
struct Open {

    static constexpr const char* name = "Open";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr Open()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Open(const std::int32_t value)
     : value{ value } {}

    // get value of Open field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
