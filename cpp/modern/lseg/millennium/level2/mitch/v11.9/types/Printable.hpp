#pragma once

#include <cstddef>

namespace lseg::millennium::level2::mitch::v11_9 {


// Printable
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
