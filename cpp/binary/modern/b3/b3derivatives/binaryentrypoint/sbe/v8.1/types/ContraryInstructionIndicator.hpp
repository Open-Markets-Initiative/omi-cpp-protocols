#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {


// contraryInstructionIndicator
struct ContraryInstructionIndicator {

    static constexpr auto name = "Contrary Instruction Indicator";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr ContraryInstructionIndicator()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ContraryInstructionIndicator(const std::uint8_t &value)
     : value{ value } {}

    // get value of ContraryInstructionIndicator field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
