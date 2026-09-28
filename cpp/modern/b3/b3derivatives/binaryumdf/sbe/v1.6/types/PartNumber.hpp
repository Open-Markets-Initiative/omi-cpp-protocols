#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// partNumber
struct PartNumber {

    static constexpr const char* name = "Part Number";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr PartNumber()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PartNumber(const std::uint16_t value)
     : value{ value } {}

    // get value of PartNumber field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
