#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Denotes the Reason Type sale condition
struct Category2 {

    static constexpr auto name = "Category 2";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Category2()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Category2(const char &value)
     : value{ value } {}

    // get value of Category2 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
