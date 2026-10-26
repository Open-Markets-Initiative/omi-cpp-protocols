#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_11_b {


// Space-filled. Field is reserved for future use
struct Reserved {

    static constexpr auto name = "Reserved";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Reserved()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Reserved(const char &value)
     : value{ value } {}

    // get value of Reserved field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
