#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for special sale condition codes. This field is case sensitive
struct SpecialSaleCondition {

    static constexpr auto name = "Special Sale Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SpecialSaleCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SpecialSaleCondition(const char &value)
     : value{ value } {}

    // get value of SpecialSaleCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
