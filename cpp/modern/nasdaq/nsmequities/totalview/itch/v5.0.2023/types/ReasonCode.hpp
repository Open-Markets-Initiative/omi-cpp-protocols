#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Trading Action reason
struct ReasonCode {

    static constexpr auto name = "Reason Code";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr ReasonCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReasonCode(const type &value)
     : value{ value } {}

    // get value of ReasonCode field
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
