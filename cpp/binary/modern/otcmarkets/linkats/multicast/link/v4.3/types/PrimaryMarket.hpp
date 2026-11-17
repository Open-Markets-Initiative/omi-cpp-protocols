// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/PrimaryMarket.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Primary trading market or exchange.
struct PrimaryMarket {

    static constexpr auto name = "Primary Market";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr PrimaryMarket()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PrimaryMarket(const type &value)
     : value{ value } {}

    // get value of PrimaryMarket field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
