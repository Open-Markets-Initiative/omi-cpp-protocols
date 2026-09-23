#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// The session ID of the session that is now logged into. Left padded with spaces.
struct AcceptedSession {

    static constexpr auto name = "Accepted Session";
    static constexpr std::size_t size = 10;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr AcceptedSession()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AcceptedSession(const type &value)
     : value{ value } {}

    // get value of AcceptedSession field
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
