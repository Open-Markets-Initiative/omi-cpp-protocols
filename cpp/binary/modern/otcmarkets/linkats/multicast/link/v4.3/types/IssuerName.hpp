// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/IssuerName.hpp
#pragma once

#include <cstddef>

namespace otcmarkets::linkats::multicast::link::v4_3 {


// Issuer name
struct IssuerName {

    static constexpr auto name = "Issuer Name";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr IssuerName()
     : value{} {}

    // standard constructor
    constexpr explicit IssuerName(const type &value)
     : value{ value } {}

    // get value of IssuerName field
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
