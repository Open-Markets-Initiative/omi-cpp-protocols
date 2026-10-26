#pragma once

#include <cstddef>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {


// Option Type
struct CallOrPut {

    static constexpr auto name = "Call Or Put";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr CallOrPut()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit CallOrPut(const char &value)
     : value{ value } {}

    // get value of CallOrPut field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
