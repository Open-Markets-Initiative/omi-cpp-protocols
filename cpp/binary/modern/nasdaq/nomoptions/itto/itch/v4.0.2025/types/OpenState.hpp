#pragma once

#include <cstddef>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {


// The allowable values are:
struct OpenState {

    static constexpr auto name = "Open State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpenState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenState(const char &value)
     : value{ value } {}

    // get value of OpenState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
