#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v13 {


// Side of order
struct Side {

    static constexpr auto name = "Side";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr Side()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Side(const std::uint8_t &value)
     : value{ value } {}

    // get value of Side field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
