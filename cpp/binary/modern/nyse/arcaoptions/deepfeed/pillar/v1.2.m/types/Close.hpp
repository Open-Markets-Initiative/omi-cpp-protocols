#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The Last price of the series for the day. Use the Price scale from the series index mapping.
struct Close {

    static constexpr const char* name = "Close";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;

    // default constructor
    constexpr Close()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Close(const std::int32_t value)
     : value{ value } {}

    // get value of Close field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
