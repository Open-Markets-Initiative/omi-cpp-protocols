#pragma once

#include <cstddef>

namespace asx::asxderivatives::ntp::itch::v1_05 {


// Indicates the current session state for the contract as per
struct SessionState {

    static constexpr auto name = "Session State";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SessionState()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SessionState(const char &value)
     : value{ value } {}

    // get value of SessionState field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
