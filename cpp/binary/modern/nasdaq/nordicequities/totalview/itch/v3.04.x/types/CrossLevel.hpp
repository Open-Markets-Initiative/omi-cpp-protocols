#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// The level the cross is being generated for
struct CrossLevel {

    static constexpr auto name = "Cross Level";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CrossLevel()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossLevel(const char &value)
     : value{ value } {}

    // get value of CrossLevel field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
