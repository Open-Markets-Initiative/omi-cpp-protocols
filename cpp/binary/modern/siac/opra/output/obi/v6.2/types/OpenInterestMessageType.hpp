#pragma once

#include <cstddef>

namespace siac::opra::output::obi::v6_2 {


// Open Interest Message Type
struct OpenInterestMessageType {

    static constexpr auto name = "Open Interest Message Type";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OpenInterestMessageType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OpenInterestMessageType(const char &value)
     : value{ value } {}

    // get value of OpenInterestMessageType field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
