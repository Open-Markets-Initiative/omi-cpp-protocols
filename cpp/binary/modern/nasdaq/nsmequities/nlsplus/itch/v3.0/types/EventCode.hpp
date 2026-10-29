#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {


// Denotes the Nls Plus type of system event for which the message is being generated
struct EventCode {

    static constexpr auto name = "Event Code";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr EventCode()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EventCode(const char &value)
     : value{ value } {}

    // get value of EventCode field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
