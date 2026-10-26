#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Contains the index value using last sale values of index components.
struct IndexValueDenominatorCode {

    static constexpr auto name = "Index Value Denominator Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IndexValueDenominatorCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndexValueDenominatorCode(const char &value)
     : value{ value } {}

    // get value of IndexValueDenominatorCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
