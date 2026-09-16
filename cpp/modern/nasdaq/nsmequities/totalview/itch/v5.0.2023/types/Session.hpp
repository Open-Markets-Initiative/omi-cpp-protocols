#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Identity of the multicast session
struct Session {

    static constexpr auto name = "Session";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Session()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Session(const type &value)
     : value{ value } {}

    // get value of Session field
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
