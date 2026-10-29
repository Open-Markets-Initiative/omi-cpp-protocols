#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {


// Reserved for future use
struct Reserved2 {

    static constexpr auto name = "Reserved 2";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Reserved2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved2(const type &value)
     : value{ value } {}

    // get value of Reserved2 field
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
