#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v8 {


// Contains the HMAC signature
struct HmacSignature {

    static constexpr auto name = "Hmac Signature";
    static constexpr std::size_t size = 32;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr HmacSignature()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit HmacSignature(const type &value)
     : value{ value } {}

    // get value of HmacSignature field
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
