#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Market Set defines the bilateral relationship and Self Match Prevention configuration for eligible markets
struct MarketSet {

    static constexpr auto name = "Market Set";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr MarketSet()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MarketSet(const type &value)
     : value{ value } {}

    // get value of MarketSet field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
