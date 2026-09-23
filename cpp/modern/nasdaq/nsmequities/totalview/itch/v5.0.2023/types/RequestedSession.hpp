#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Specifies the session the client would like to log into, or all blanks to log into the currently active session.
struct RequestedSession {

    static constexpr auto name = "Requested Session";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr RequestedSession()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RequestedSession(const type &value)
     : value{ value } {}

    // get value of RequestedSession field
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
