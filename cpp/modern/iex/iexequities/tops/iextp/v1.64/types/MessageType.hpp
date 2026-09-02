#pragma once

#include <cstddef>

namespace iex::iexequities::tops::iextp::v1_64 {


// Code identifying this message type
struct MessageType {

    static constexpr auto name = "Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageType(const char &value)
     : value{ value } {}

    // get value of MessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
