#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// SRO Trade Detail
struct Category4 {

    static constexpr auto name = "Category 4";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Category4()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Category4(const char &value)
     : value{ value } {}

    // get value of Category4 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
