#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::opra::output::obi::v6_2 {


// Identifies the unique symbol assigned to the underlying security.
struct SecuritySymbolShort {

    static constexpr auto name = "Security Symbol Short";
    static constexpr std::size_t size = 4;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SecuritySymbolShort()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecuritySymbolShort(const type &value)
     : value{ value } {}

    // get value of SecuritySymbolShort field
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
