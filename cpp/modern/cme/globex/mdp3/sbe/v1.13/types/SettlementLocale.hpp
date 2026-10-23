#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// Settlement Locale. Optionally used to differentiate settlement location
struct SettlementLocale {

    static constexpr auto name = "Settlement Locale";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SettlementLocale()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlementLocale(const type &value)
     : value{ value } {}

    // get value of SettlementLocale field
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
