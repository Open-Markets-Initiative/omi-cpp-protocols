#pragma once

#include <cstddef>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {


// Order Type of CUBE/BOLD/COA
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
