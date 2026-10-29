#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Order Type of CUBE/Bold/COA
struct Type {

    static constexpr auto name = "Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Type()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Type(const char &value)
     : value{ value } {}

    // get value of Type field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
