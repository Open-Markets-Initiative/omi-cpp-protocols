#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v8 {


// ISO standard instrument categorization code
struct CfiCode {

    static constexpr auto name = "Cfi Code";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr CfiCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CfiCode(const type &value)
     : value{ value } {}

    // get value of CfiCode field
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
