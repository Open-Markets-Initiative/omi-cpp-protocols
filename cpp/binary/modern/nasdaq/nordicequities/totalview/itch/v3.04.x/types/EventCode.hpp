#pragma once

#include <cstddef>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {


// System event code
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
