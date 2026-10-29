#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Denotes the Reg Sho short sale price test restriction status for the issue
struct RegShoAction {

    static constexpr auto name = "Reg Sho Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr RegShoAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit RegShoAction(const char &value)
     : value{ value } {}

    // get value of RegShoAction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
