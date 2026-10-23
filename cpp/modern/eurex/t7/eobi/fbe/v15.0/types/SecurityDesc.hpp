#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace eurex::t7::eobi::fbe::v15_0 {


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
