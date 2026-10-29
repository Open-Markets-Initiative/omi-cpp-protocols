#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Denotes the Settlement Type sale condition
struct Category1 {

    static constexpr auto name = "Category 1";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Category1()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Category1(const char &value)
     : value{ value } {}

    // get value of Category1 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
