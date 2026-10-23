#pragma once

#include <bit>
#include <cstddef>
#include <cstdint>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// The Contract Unit as specified in the ASX 24 Contract Specifications.
struct LotSizeOrFaceValue {

    static constexpr const char* name = "Lot Size Or Face Value";
    static constexpr std::size_t size =  8;
    using type = std::uint64_t;

    // default constructor
    constexpr LotSizeOrFaceValue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LotSizeOrFaceValue(const std::uint64_t value)
     : value{ std::byteswap(value) } {}

    // get value of LotSizeOrFaceValue field
    [[nodiscard]] std::uint64_t get() const {
        return std::byteswap(value);
    }

  protected:
    std::uint64_t value;
};
}
