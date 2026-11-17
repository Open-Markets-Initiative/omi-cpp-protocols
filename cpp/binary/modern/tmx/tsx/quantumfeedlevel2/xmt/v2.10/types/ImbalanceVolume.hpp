// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/ImbalanceVolume.hpp
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

    // default constructor: the null the model states, where it states one
    constexpr ImbalanceVolume()
     : value{ no_value } {}

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
