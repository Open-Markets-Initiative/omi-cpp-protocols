#pragma once

#include <cstddef>

namespace databento::marketdata::normalized::dbn::v1 {


// The event action
struct Action {

    static constexpr auto name = "Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Action()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Action(const char &value)
     : value{ value } {}

    // get value of Action field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
