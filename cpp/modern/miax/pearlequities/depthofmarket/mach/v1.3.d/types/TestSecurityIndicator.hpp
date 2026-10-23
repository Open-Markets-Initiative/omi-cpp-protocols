#pragma once

#include <cstddef>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {


// Y - Yes, N - No.
struct TestSecurityIndicator {

    static constexpr auto name = "Test Security Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr TestSecurityIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TestSecurityIndicator(const char &value)
     : value{ value } {}

    // get value of TestSecurityIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
