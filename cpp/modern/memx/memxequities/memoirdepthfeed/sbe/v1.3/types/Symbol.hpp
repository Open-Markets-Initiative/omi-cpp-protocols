#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {


// Symbol
struct Symbol {

    static constexpr auto name = "Symbol";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Symbol()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Symbol(const type &value)
     : value{ value } {}

    // get value of Symbol field
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
