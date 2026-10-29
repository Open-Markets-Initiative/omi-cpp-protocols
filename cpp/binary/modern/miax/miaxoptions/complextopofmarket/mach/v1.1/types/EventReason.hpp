#pragma once

#include <cstddef>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {


// Values: “A” = This event resulted from automatic/market driven event “M” = MIAX manually initiated this event
struct EventReason {

    static constexpr auto name = "Event Reason";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr EventReason()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventReason(const char &value)
     : value{ value } {}

    // get value of EventReason field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
