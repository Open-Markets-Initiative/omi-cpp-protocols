#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace eurex::t7::eobi::fbe::v13_0 {


// 
struct SecurityDesc {

    static constexpr auto name = "Security Desc";
    static constexpr std::size_t size = 40;

    // underlying type
    using type = std::array<char, size>;

    // whether the optional SecurityDesc field is present
    [[nodiscard]] bool has_value() const {
        return value[0] != '\0';
    }

    // default constructor
    constexpr SecurityDesc()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityDesc(const type &value)
     : value{ value } {}

    // get value of SecurityDesc field
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
