#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Round Lot size in shares.
struct LotSize {

    static constexpr const char* name = "Lot Size";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr LotSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LotSize(const std::uint16_t value)
     : value{ value } {}

    // get value of LotSize field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
