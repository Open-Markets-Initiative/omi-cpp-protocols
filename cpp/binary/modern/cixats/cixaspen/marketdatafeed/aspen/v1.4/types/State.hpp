#pragma once

#include <cstddef>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {


// Symbol trading state
struct State {

    static constexpr auto name = "State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr State()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit State(const char &value)
     : value{ value } {}

    // get value of State field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
