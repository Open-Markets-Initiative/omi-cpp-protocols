#pragma once

#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// ShortSaleRestriction
struct ShortSaleRestriction {

    static constexpr auto name = "Short Sale Restriction";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ShortSaleRestriction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortSaleRestriction(const std::uint8_t &value)
     : value{ value } {}

    // get value of ShortSaleRestriction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
