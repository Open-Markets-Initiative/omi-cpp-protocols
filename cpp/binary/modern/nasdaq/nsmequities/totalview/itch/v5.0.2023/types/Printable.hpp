#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates if the execution should be reflected on time and sale displays and volume calculations
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
