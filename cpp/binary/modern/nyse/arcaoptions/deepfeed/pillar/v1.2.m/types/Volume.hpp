#pragma once

#include <cstddef>
#include <cstdint>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The order quantity in contracts
struct Volume {

    static constexpr const char* name = "Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr Volume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Volume(const std::uint32_t value)
     : value{ value } {}

    // get value of Volume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
