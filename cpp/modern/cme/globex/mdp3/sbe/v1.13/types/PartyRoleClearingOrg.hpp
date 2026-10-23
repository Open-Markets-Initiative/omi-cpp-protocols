#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Clearing organization
struct PartyRoleClearingOrg {

    static constexpr auto name = "Party Role Clearing Org";
    static constexpr std::size_t size = 5;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr PartyRoleClearingOrg()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PartyRoleClearingOrg(const type &value)
     : value{ value } {}

    // get value of PartyRoleClearingOrg field
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
