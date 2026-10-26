#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// Human-readable long name
struct LongName {

    static constexpr auto name = "Long Name";
    static constexpr std::size_t size = 32;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr LongName()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LongName(const type &value)
     : value{ value } {}

    // get value of LongName field
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
