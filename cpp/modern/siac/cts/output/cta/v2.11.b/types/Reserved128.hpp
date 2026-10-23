#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace siac::cts::output::cta::v2_11_b {


// Space-filled. Field is reserved for future use
struct Reserved128 {

    static constexpr auto name = "Reserved 128";
    static constexpr std::size_t size = 128;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Reserved128()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved128(const type &value)
     : value{ value } {}

    // get value of Reserved128 field
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
