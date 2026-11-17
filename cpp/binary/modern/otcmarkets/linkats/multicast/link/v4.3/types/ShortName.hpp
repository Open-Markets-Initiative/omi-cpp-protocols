// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/ShortName.hpp
#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Short name of the security.
struct ShortName {

    static constexpr auto name = "Short Name";
    static constexpr std::size_t size = 25;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ShortName()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ShortName(const type &value)
     : value{ value } {}

    // get value of ShortName field
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
