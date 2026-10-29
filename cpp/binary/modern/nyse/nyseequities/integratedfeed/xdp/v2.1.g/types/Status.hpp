#pragma once

#include <cstddef>

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {


// The reason why the request was rejected.
struct Status {

    static constexpr auto name = "Status";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Status()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Status(const char &value)
     : value{ value } {}

    // get value of Status field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
