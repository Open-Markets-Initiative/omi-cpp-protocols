#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for special sale condition codes. This field is case sensitive
struct OriginalSpecialSaleCondition {

    static constexpr auto name = "Original Special Sale Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginalSpecialSaleCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalSpecialSaleCondition(const char &value)
     : value{ value } {}

    // get value of OriginalSpecialSaleCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
