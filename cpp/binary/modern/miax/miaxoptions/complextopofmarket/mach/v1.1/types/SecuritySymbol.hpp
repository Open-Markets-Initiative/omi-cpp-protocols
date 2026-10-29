#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Option Security Symbol
struct SecuritySymbol {

    static constexpr auto name = "Security Symbol";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecuritySymbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecuritySymbol(const type &value)
     : value{ value } {}

    // get value of SecuritySymbol field
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
