#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {


// numInGroup
struct NumInGroup {

    static constexpr auto name = "Num In Group";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr NumInGroup()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit NumInGroup(const std::uint8_t &value)
     : value{ value } {}

    // get value of NumInGroup field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
