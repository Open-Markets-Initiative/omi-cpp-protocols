#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Extended Hours or Sold codes
struct OriginalExtendedHoursOrSoldCode {

    static constexpr auto name = "Original Extended Hours Or Sold Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OriginalExtendedHoursOrSoldCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OriginalExtendedHoursOrSoldCode(const char &value)
     : value{ value } {}

    // get value of OriginalExtendedHoursOrSoldCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
