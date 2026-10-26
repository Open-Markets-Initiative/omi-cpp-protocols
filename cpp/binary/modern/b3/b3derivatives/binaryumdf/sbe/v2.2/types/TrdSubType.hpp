#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {


// trdSubType
struct TrdSubType {

    static constexpr auto name = "Trd Sub Type";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 0;

    // default constructor
    constexpr TrdSubType()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit TrdSubType(const std::uint8_t &value)
     : value{ value } {}

    // get value of TrdSubType field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
