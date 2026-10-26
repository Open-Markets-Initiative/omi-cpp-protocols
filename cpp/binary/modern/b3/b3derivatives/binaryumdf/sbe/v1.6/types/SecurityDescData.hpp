#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// textual description for the financial instrument
struct SecurityDescData {

    static constexpr auto name = "Security Desc Data";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityDescData()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityDescData(const char &value)
     : value{ value } {}

    // get value of SecurityDescData field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
