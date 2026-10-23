#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Nano-seconds portion of the expected time of the event. Specifies number of nano-seconds since the seconds specified in "Expected Event Time Seconds" field.
struct ExpectedEventTimeNanoSecondsPart {

    static constexpr const char* name = "Expected Event Time Nano Seconds Part";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr ExpectedEventTimeNanoSecondsPart()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit ExpectedEventTimeNanoSecondsPart(const std::uint32_t value)
     : value{ value } {}

    // get value of ExpectedEventTimeNanoSecondsPart field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
