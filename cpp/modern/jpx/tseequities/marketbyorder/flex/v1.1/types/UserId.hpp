#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// User ID for login authentication
struct UserId {

    static constexpr auto name = "User Id";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr UserId()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UserId(const type &value)
     : value{ value } {}

    // get value of UserId field
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
