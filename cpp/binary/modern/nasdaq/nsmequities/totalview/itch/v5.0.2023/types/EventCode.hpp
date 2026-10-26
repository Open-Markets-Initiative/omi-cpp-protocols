#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// System Event Codes
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
