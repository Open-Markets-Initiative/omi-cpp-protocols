#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// year
struct Year {

    static constexpr const char* name = "Year";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr Year()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit Year(const std::uint16_t value)
     : value{ value } {}

    // get value of Year field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
