#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {


// Free form human readable text
struct DebugText {

    static constexpr auto name = "Debug Text";
    static constexpr std::size_t size = 0;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr DebugText()
     : value{} {}

    // standard constructor
    constexpr explicit DebugText(const type &value)
     : value{ value } {}

    // get value of DebugText field
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
