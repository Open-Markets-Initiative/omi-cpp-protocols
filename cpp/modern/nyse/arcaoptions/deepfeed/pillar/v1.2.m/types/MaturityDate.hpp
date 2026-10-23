#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Option maturity date - YYMMDD
struct MaturityDate {

    static constexpr auto name = "Maturity Date";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr MaturityDate()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MaturityDate(const type &value)
     : value{ value } {}

    // get value of MaturityDate field
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
