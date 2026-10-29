#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Extended Hours or Sold codes
struct CorrectedExtendedHoursOrSoldCode {

    static constexpr auto name = "Corrected Extended Hours Or Sold Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CorrectedExtendedHoursOrSoldCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CorrectedExtendedHoursOrSoldCode(const char &value)
     : value{ value } {}

    // get value of CorrectedExtendedHoursOrSoldCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
