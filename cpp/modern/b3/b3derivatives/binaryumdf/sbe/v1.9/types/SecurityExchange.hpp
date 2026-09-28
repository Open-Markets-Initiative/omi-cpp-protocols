#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {


// securityExchange
struct SecurityExchange {

    static constexpr auto name = "Security Exchange";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecurityExchange()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityExchange(const type &value)
     : value{ value } {}

    // get value of SecurityExchange field
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
