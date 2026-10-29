#pragma once

#include <cstddef>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {


// Reserved for future use
struct Offical {

    static constexpr auto name = "Offical";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Offical()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Offical(const char &value)
     : value{ value } {}

    // get value of Offical field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
