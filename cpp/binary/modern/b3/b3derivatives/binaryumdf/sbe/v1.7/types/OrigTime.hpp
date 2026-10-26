#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {


// origTime
struct OrigTime {

    static constexpr auto name = "Orig Time";
    static constexpr std::size_t size = 8;

    // underlying type
    using type = std::uint64_t;
static const type no_value = 0;

    // default constructor
    constexpr OrigTime()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit OrigTime(const std::uint64_t &value)
     : value{ value } {}

    // get value of OrigTime field
    [[nodiscard]] std::uint64_t get() const {
        return value;
    }

  protected:
    std::uint64_t value;
};
}
