#pragma once

#include <cstddef>

namespace nasdaq::psxequities::totalview::itch::v5_0 {


// Indicates the current operational halting status of the identified market
struct OperationalHaltAction {

    static constexpr auto name = "Operational Halt Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr OperationalHaltAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OperationalHaltAction(const char &value)
     : value{ value } {}

    // get value of OperationalHaltAction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
