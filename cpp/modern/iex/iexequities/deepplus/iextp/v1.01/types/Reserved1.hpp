#pragma once

#include <cstddef>

namespace iex::iexequities::deepplus::iextp::v1_01 {


// Reserved for future use
struct Reserved1 {

    static constexpr auto name = "Reserved 1";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Reserved1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved1(const char &value)
     : value{ value } {}

    // get value of Reserved1 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
