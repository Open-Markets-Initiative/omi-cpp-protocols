#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {


// Indicates if the NASDAQ security is set up for IPO release. This field is intended to help NASDAQ market participant firms comply with FINRA Rule 5131(b).
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
