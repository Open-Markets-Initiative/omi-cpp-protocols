#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// Whether the cross has been extended
struct Extension {

    static constexpr auto name = "Extension";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Extension()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Extension(const char &value)
     : value{ value } {}

    // get value of Extension field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
