#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v1_91 {


// Indices message type
struct IndicesMessageType {

    static constexpr auto name = "Indices Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr IndicesMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit IndicesMessageType(const char &value)
     : value{ value } {}

    // get value of IndicesMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
