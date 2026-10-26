#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Interest Flag
struct InterestFlag {

    static constexpr auto name = "Interest Flag";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr InterestFlag()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InterestFlag(const char &value)
     : value{ value } {}

    // get value of InterestFlag field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
