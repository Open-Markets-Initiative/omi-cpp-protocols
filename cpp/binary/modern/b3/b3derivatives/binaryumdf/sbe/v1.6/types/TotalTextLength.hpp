#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// totalTextLength
struct TotalTextLength {

    static constexpr const char* name = "Total Text Length";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr TotalTextLength()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TotalTextLength(const std::uint32_t value)
     : value{ value } {}

    // get value of TotalTextLength field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
