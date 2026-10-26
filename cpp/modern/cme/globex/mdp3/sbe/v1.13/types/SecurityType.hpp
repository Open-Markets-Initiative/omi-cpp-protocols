#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Security Type
struct SecurityType {

    static constexpr auto name = "Security Type";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecurityType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityType(const type &value)
     : value{ value } {}

    // get value of SecurityType field
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
