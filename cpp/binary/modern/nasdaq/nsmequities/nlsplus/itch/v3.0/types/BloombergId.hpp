#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Bloomberg global identifier for the issue
struct BloombergId {

    static constexpr auto name = "Bloomberg Id";
    static constexpr std::size_t size = 12;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr BloombergId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit BloombergId(const type &value)
     : value{ value } {}

    // get value of BloombergId field
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
