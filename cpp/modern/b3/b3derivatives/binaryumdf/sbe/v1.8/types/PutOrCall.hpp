#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {


// putOrCall
struct PutOrCall {

    static constexpr auto name = "Put Or Call";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;
static const type no_value = 255;

    // default constructor
    constexpr PutOrCall()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit PutOrCall(const std::uint8_t &value)
     : value{ value } {}

    // get value of PutOrCall field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
