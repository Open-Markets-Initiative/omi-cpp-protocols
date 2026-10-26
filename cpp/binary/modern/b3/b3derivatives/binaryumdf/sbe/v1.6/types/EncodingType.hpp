#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// Identifier of the encoding used in the message payload
struct EncodingType {

    static constexpr const char* name = "Encoding Type";
    static constexpr std::size_t size =  2;
    using type = std::uint16_t;

    // default constructor
    constexpr EncodingType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit EncodingType(const std::uint16_t value)
     : value{ value } {}

    // get value of EncodingType field
    [[nodiscard]] std::uint16_t get() const {
        return value;
    }

  protected:
    std::uint16_t value;
};
}
