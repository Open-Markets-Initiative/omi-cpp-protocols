#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// securityUpdateAction
struct SecurityUpdateAction {

    static constexpr auto name = "Security Update Action";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityUpdateAction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityUpdateAction(const char &value)
     : value{ value } {}

    // get value of SecurityUpdateAction field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
