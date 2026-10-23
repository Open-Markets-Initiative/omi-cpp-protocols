#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Name of security issuer or the Legal Entity Identifier (LEI - the International ISO standard 17442)
struct Issuer {

    static constexpr auto name = "Issuer";
    static constexpr std::size_t size = 25;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Issuer()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Issuer(const type &value)
     : value{ value } {}

    // get value of Issuer field
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
