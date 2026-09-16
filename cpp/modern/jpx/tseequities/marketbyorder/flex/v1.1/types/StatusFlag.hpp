#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// Indicates trading status
struct StatusFlag {

    static constexpr auto name = "Status Flag";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr StatusFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit StatusFlag(const type &value)
     : value{ value } {}

    // get value of StatusFlag field
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
