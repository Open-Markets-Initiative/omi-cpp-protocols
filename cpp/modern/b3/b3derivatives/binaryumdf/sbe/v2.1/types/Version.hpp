#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// Schema version
struct Version {

    static constexpr const char* name = "Version";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;
static const type static_value = 15;

    // default constructor
    constexpr Version()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Version(const std::uint16_t value)
     : value{ value } {}

    // get value of Version field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
