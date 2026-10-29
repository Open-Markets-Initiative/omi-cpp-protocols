#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Indicates the basis of the reference price for net change calculations
struct ReferenceForNetChange {

    static constexpr auto name = "Reference For Net Change";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ReferenceForNetChange()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ReferenceForNetChange(const char &value)
     : value{ value } {}

    // get value of ReferenceForNetChange field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
