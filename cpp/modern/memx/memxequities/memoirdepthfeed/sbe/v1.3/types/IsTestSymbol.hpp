#pragma once

#include <cstddef>
#include <cstdint>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// IsTestSymbol
struct IsTestSymbol {

    static constexpr auto name = "Is Test Symbol";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr IsTestSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IsTestSymbol(const std::uint8_t &value)
     : value{ value } {}

    // get value of IsTestSymbol field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
