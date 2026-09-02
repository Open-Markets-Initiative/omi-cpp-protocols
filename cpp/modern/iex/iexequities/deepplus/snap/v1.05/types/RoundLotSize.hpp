#pragma once

#include <cstddef>
#include <cstdint>

namespace iex::iexequities::deepplus::snap::v1_05 {

// Number of shares that represent a round lot
struct RoundLotSize {

    static constexpr const char* name = "Round Lot Size";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr RoundLotSize()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RoundLotSize(const std::uint32_t value)
     : value{ value } {}

    // get value of RoundLotSize field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
