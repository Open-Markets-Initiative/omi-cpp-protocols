#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Country of Origin, ISO alpha-2 country code
struct CountryOfIssue {

    static constexpr auto name = "Country Of Issue";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr CountryOfIssue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CountryOfIssue(const type &value)
     : value{ value } {}

    // get value of CountryOfIssue field
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
