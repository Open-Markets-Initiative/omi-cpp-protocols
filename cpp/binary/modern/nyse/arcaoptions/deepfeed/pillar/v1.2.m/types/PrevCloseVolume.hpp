#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The previous day's closing volume for the security.
struct PrevCloseVolume {

    static constexpr const char* name = "Prev Close Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr PrevCloseVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrevCloseVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of PrevCloseVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
