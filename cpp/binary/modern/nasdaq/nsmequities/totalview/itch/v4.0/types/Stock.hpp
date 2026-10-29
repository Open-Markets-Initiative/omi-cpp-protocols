#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {


// Denotes the security symbol for the issue in NASDAQ Single Book. Refer to Appendix NASDAQ Single Book stock symbol convention information.
struct Stock {

    static constexpr auto name = "Stock";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Stock()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Stock(const type &value)
     : value{ value } {}

    // get value of Stock field
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
