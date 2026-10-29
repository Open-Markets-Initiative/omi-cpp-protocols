#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Indicates if the Nasdaq security is set up for Ipo release
struct IpoFlag {

    static constexpr auto name = "Ipo Flag";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IpoFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IpoFlag(const char &value)
     : value{ value } {}

    // get value of IpoFlag field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
