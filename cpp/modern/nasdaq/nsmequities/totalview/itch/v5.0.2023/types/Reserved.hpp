#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Reserved
struct Reserved {

    static constexpr auto name = "Reserved";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Reserved()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved(const char &value)
     : value{ value } {}

    // get value of Reserved field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
