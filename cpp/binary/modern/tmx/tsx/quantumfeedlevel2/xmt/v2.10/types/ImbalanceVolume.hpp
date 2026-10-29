#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Identifies The Volume Of Shares Of The Imbalance Side For Market On Close
struct ImbalanceVolume {

    static constexpr const char* name = "Imbalance Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor
    constexpr ImbalanceVolume()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ImbalanceVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of ImbalanceVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
