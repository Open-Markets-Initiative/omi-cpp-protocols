#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Message identifier
struct MessageIndicator {

    static constexpr auto name = "Message Indicator";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr MessageIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit MessageIndicator(const char &value)
     : value{ value } {}

    // get value of MessageIndicator field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
