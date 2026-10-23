#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Free format text string. May include logout confirmation or reason for logout
struct LogoutText {

    static constexpr auto name = "Logout Text";
    static constexpr std::size_t size = 180;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr LogoutText()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit LogoutText(const type &value)
     : value{ value } {}

    // get value of LogoutText field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field
    [[nodiscard]] std::size_t length() const {
        std::size_t index = 0;
        for (; index < size; ++index) {
            if (value[index] == '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
