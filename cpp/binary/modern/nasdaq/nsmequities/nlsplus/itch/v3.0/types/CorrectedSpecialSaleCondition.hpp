#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for special sale condition codes. This field is case sensitive
struct CorrectedSpecialSaleCondition {

    static constexpr auto name = "Corrected Special Sale Condition";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CorrectedSpecialSaleCondition()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedSpecialSaleCondition(const char &value)
     : value{ value } {}

    // get value of CorrectedSpecialSaleCondition field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
