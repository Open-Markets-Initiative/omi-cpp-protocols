#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Reserved for future use
struct Opening {

    static constexpr auto name = "Opening";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Opening()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Opening(const char &value)
     : value{ value } {}

    // get value of Opening field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
