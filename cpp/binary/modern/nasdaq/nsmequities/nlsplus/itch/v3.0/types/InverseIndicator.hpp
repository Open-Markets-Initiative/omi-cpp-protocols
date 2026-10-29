#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Indicates the directional relationship between the Etp and the underlying index
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
