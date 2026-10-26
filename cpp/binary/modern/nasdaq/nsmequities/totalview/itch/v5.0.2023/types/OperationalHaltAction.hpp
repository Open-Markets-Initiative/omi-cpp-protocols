#pragma once

#include <cstddef>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {


// Indicates the operational halt action for the security
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
