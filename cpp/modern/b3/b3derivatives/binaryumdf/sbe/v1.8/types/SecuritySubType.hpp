#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// securitySubType
struct SecuritySubType {

    static constexpr const char* name = "Security Sub Type";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr SecuritySubType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecuritySubType(const std::uint16_t value)
     : value{ value } {}

    // get value of SecuritySubType field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
