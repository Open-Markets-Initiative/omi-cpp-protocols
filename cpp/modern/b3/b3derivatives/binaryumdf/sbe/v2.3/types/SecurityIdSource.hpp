#pragma once

#include <cstddef>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {


// securityIDSource
struct SecurityIdSource {

    static constexpr auto name = "Security Id Source";
    static constexpr std::size_t size = 1;

    // default constructor
    constexpr SecurityIdSource()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecurityIdSource(const char &value)
     : value{ value } {}

    // get value of SecurityIdSource field
    [[nodiscard]] char get() const {
        return value;
    }

  protected:
    char value;
};
}
