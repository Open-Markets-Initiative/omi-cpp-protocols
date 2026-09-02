#pragma once

#include <cstddef>

namespace iex::iexequities::deep::iextp::v1_06 {


// Security event identifier
struct SecurityEvent {

    static constexpr auto name = "Security Event";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityEvent()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityEvent(const char &value)
     : value{ value } {}

    // get value of SecurityEvent field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
