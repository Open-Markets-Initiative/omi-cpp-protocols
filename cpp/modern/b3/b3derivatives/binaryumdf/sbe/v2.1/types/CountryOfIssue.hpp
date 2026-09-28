#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {


// countryOfIssue
struct CountryOfIssue {

    static constexpr auto name = "Country Of Issue";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // whether the optional CountryOfIssue field is present
    [[nodiscard]] bool has_value() const {
        return value[0] != '\0';
    }

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
