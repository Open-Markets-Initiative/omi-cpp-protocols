#pragma once

#include <cstddef>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {


// First byte of the tag identifying the message type used as dispatch key
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
