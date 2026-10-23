#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Risk Set identifies the list of instruments sharing credit limits set up
struct RiskSet {

    static constexpr auto name = "Risk Set";
    static constexpr std::size_t size = 6;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr RiskSet()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RiskSet(const type &value)
     : value{ value } {}

    // get value of RiskSet field
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
