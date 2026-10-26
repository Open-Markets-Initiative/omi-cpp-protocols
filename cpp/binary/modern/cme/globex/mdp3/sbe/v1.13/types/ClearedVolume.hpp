#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {

// The total cleared volume of instrument traded during the prior trading session.
struct ClearedVolume {

    static constexpr const char* name = "Cleared Volume";
    static constexpr std::size_t size =  4;
    using type = std::int32_t;
static const type no_value = 2147483647;

    // default constructor
    constexpr ClearedVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ClearedVolume(const std::int32_t value)
     : value{ value } {}

    // get value of ClearedVolume field
    [[nodiscard]] std::int32_t get() const {
        return value;
    }

  protected:
    std::int32_t value;
};
}
