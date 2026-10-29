#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// Control message type
struct ControlMessageType {

    static constexpr auto name = "Control Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr ControlMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ControlMessageType(const char &value)
     : value{ value } {}

    // get value of ControlMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
