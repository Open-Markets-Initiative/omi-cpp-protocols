#pragma once

#include <cstddef>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {


// Issue Values
struct Issue {

    static constexpr auto name = "Issue";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Issue()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Issue(const char &value)
     : value{ value } {}

    // get value of Issue field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
