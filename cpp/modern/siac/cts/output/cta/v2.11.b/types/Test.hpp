#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Identifies whether the security symbol is a test symbol
struct Test {

    static constexpr auto name = "Test";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Test()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Test(const char &value)
     : value{ value } {}

    // get value of Test field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
