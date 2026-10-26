#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// Whether the execution should be reflected in statistics
struct Printable {

    static constexpr auto name = "Printable";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Printable()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Printable(const char &value)
     : value{ value } {}

    // get value of Printable field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
