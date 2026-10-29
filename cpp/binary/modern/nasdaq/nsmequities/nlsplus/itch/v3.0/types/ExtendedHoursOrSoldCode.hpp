#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Used for Extended Hours or Sold codes
struct ExtendedHoursOrSoldCode {

    static constexpr auto name = "Extended Hours Or Sold Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ExtendedHoursOrSoldCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExtendedHoursOrSoldCode(const char &value)
     : value{ value } {}

    // get value of ExtendedHoursOrSoldCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
