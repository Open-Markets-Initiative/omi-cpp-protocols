#pragma once

#include <cstddef>

namespace iex::iexequities::deepplus::iextp::v1_01 {


// Detail of the Reg. SHO short sale price test restriction status
struct Detail {

    static constexpr auto name = "Detail";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Detail()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Detail(const char &value)
     : value{ value } {}

    // get value of Detail field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
