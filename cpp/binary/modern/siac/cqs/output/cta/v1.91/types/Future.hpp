#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v1_91 {


// Field is reserved for future use.
struct Future {

    static constexpr auto name = "Future";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Future()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Future(const char &value)
     : value{ value } {}

    // get value of Future field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
