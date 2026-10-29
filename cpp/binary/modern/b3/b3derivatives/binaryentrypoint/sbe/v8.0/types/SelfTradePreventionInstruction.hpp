#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {


// selfTradePreventionInstruction
struct SelfTradePreventionInstruction {

    static constexpr auto name = "Self Trade Prevention Instruction";
    static constexpr std::size_t size = 1;
    using type = std::uint8_t;

    // default constructor
    constexpr SelfTradePreventionInstruction()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SelfTradePreventionInstruction(const std::uint8_t &value)
     : value{ value } {}

    // get value of SelfTradePreventionInstruction field
    [[nodiscard]] std::uint8_t get() const {
        return value;
    }

  protected:
    std::uint8_t value;
};
}
