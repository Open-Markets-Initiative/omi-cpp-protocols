#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Aggregate book level
struct MdPriceLevel {

    static constexpr auto name = "Md Price Level";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr MdPriceLevel()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MdPriceLevel(const std::uint8_t &value)
     : value{ value } {}

    // get value of MdPriceLevel field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
