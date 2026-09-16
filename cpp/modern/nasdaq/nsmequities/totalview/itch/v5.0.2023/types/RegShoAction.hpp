#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Denotes the Reg SHO Short Sale Price Test Restriction status for the issue at the time of the message dissemination
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
