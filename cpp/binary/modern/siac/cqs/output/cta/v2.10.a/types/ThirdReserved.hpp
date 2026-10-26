#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Space-filled. Field is reserved for future use
struct ThirdReserved {

    static constexpr auto name = "Third Reserved";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ThirdReserved()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ThirdReserved(const char &value)
     : value{ value } {}

    // get value of ThirdReserved field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
