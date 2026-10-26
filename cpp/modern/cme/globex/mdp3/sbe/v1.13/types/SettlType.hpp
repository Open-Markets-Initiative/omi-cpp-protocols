#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace cme::mdp3::v13 {


// For SPOTs will contain 0. For Fixed date NDFs will contain the value 'B'. For the standard NDFs tenors expressed using Dx, Mx, Wx, and Yx values, where 'x' does not denote business days, but calendar days
struct SettlType {

    static constexpr auto name = "Settl Type";
    static constexpr std::size_t size = 3;

    // underlying type
    using type = std::array<char, size>;

    // default constructor
    constexpr SettlType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SettlType(const type &value)
     : value{ value } {}

    // get value of SettlType field
    [[nodiscard]] std::string get() const {
        return std::string{value.data(), length()};
    }

    // runtime length of field: its characters up to the fill after the last of them, so a space
    // or a null inside the text is kept
    [[nodiscard]] std::size_t length() const {
        std::size_t index = size;
        for (; index > 0; --index) {
            if (value[index - 1] != '\0') { break; }
        }

        return index;
    }

  protected:
    type value;
};
}
