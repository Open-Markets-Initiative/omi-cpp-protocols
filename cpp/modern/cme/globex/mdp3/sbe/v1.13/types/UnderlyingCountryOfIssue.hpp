#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Underlying Security's CountryOfIssue. See CountryOfIssue (470) field for description
struct UnderlyingCountryOfIssue {

    static constexpr auto name = "Underlying Country Of Issue";
    static constexpr std::size_t size = 2;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr UnderlyingCountryOfIssue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit UnderlyingCountryOfIssue(const type &value)
     : value{ value } {}

    // get value of UnderlyingCountryOfIssue field
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
