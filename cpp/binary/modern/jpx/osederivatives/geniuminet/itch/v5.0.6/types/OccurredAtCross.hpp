#pragma once

#include <cstddef>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {


// Y=Yes, N=No
struct OccurredAtCross {

    static constexpr auto name = "Occurred At Cross";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OccurredAtCross()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OccurredAtCross(const char &value)
     : value{ value } {}

    // get value of OccurredAtCross field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
