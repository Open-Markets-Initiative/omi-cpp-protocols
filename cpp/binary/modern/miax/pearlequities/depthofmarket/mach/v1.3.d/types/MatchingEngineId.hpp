#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Matching Engine that originated the packet
struct MatchingEngineId {

    static constexpr auto name = "Matching Engine Id";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MatchingEngineId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MatchingEngineId(const std::uint8_t &value)
     : value{ value } {}

    // get value of MatchingEngineId field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
