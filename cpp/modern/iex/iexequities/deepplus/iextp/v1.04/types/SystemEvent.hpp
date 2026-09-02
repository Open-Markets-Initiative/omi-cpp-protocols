#pragma once

#include <cstddef>

namespace iex::iexequities::deepplus::iextp::v1_04 {


// System event identifier
struct SystemEvent {

    static constexpr auto name = "System Event";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SystemEvent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SystemEvent(const char &value)
     : value{ value } {}

    // get value of SystemEvent field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
