#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates the directional relationship between the ETP and underlying index. Example: An ETP Leverage Factor of 3 and an Inverse value of 'Y' indicates the ETP will decrease by a value of 3.
struct InverseIndicator {

    static constexpr auto name = "Inverse Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr InverseIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit InverseIndicator(const char &value)
     : value{ value } {}

    // get value of InverseIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
