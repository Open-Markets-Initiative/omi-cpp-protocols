#pragma once

#include <cstddef>
#include <cstdint>

namespace cme::mdp3::v9 {


// Side requested
struct Side {

    static constexpr auto name = "Side";
    static constexpr std::size_t size = 1;
    using type = std::int8_t;
static const type no_value = 127;

    // default constructor
    constexpr Side()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Side(const std::int8_t &value)
     : value{ value } {}

    // get value of Side field
    [[nodiscard]] std::int8_t get() const {
        return value;
    }

  protected:
    std::int8_t value;
};
}
