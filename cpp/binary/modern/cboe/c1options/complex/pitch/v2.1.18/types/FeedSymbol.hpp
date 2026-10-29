#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::c1options::complex::pitch::v2_1_18 {


// Symbol right padded with spaces.
struct FeedSymbol {

    static constexpr auto name = "Feed Symbol";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr FeedSymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit FeedSymbol(const type &value)
     : value{ value } {}

    // get value of FeedSymbol field
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
