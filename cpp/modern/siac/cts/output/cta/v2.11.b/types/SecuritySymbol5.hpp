#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cts::output::cta::v2_11_b {


// Identifies the Security Symbol. Left justified, space-filled
struct SecuritySymbol5 {

    static constexpr auto name = "Security Symbol 5";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecuritySymbol5()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecuritySymbol5(const type &value)
     : value{ value } {}

    // get value of SecuritySymbol5 field
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
