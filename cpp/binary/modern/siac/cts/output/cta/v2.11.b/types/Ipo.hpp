#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies whether the security symbol is an IPO
struct Ipo {

    static constexpr auto name = "Ipo";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Ipo()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Ipo(const char &value)
     : value{ value } {}

    // get value of Ipo field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
