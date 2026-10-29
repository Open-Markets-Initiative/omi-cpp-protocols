#pragma once

#include <cstddef>

namespace siac::cts::output::cta::v2_9 {


// The Message Category represents the message classification
struct MessageCategory {

    static constexpr auto name = "Message Category";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MessageCategory()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageCategory(const char &value)
     : value{ value } {}

    // get value of MessageCategory field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
