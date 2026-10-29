#pragma once

#include <cstddef>

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {


// Session state event code
struct Event {

    static constexpr auto name = "Event";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr Event()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Event(const char &value)
     : value{ value } {}

    // get value of Event field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
