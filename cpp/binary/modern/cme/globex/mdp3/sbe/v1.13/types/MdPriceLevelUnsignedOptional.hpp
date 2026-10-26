#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Aggregate book level
struct MdPriceLevelUnsignedOptional {

    static constexpr auto name = "Md Price Level Unsigned Optional";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr MdPriceLevelUnsignedOptional()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdPriceLevelUnsignedOptional(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdPriceLevelUnsignedOptional field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
