#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {


// aggressorTime
struct AggressorTime {

    static constexpr auto name = "Aggressor Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr AggressorTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit AggressorTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of AggressorTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
