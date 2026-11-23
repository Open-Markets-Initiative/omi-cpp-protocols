// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/PairedVolume.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// The Number Of Moc And Loc Shares That Are Able Be Matched At The Reference Price
struct PairedVolume {

    static constexpr const char* name = "Paired Volume";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;
static const type no_value = 0;

    // default constructor: the null the model states, where it states one
    constexpr PairedVolume()
     : value{ no_value } {}

    // standard constructor
    constexpr explicit PairedVolume(const std::uint32_t value)
     : value{ value } {}

    // get value of PairedVolume field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
