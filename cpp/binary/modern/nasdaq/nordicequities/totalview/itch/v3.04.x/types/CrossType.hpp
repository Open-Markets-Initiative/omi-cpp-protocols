#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// The cross session the message is generated for
struct CrossType {

    static constexpr auto name = "Cross Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CrossType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CrossType(const char &value)
     : value{ value } {}

    // get value of CrossType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
