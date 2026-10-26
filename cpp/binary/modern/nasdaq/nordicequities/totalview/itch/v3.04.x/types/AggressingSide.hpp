#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// Side of the incoming aggressive order
struct AggressingSide {

    static constexpr auto name = "Aggressing Side";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr AggressingSide()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AggressingSide(const char &value)
     : value{ value } {}

    // get value of AggressingSide field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
