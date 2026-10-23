#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace lseg::lse::level2mbo::gtp::v26_2 {


// Identity of trading participant that submitted the order.
struct Participant {

    static constexpr auto name = "Participant";
    static constexpr std::size_t size = 11;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr Participant()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Participant(const type &value)
     : value{ value } {}

    // get value of Participant field
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
