#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Space-filled. Field is reserved for future use
struct SecondReserved {

    static constexpr auto name = "Second Reserved";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecondReserved()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecondReserved(const char &value)
     : value{ value } {}

    // get value of SecondReserved field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
