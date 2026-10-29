#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Denotes the Sequence Type sale condition
struct Category3 {

    static constexpr auto name = "Category 3";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Category3()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Category3(const char &value)
     : value{ value } {}

    // get value of Category3 field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
