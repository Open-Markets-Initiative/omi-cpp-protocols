#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Six character, base 62 symbol.
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

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == ' ') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
