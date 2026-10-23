#pragma once

#include <cstddef>

namespace siac::cqs::output::cta::v2_10_a {


// Identifies the type of Control message
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
