#pragma once

#include <cstddef>
#include <cstdint>

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Seconds portion of the expected time of the event. Always use in conjunction with the Nano-seconds part field.
struct SecondsPart {

    static constexpr const char* name = "Seconds Part";
    static constexpr std::size_t size =  4;
    using type = std::uint32_t;

    // default constructor
    constexpr SecondsPart()
     : value{ 0 } {}

    // standard constructor
    constexpr explicit SecondsPart(const std::uint32_t value)
     : value{ value } {}

    // get value of SecondsPart field
    [[nodiscard]] std::uint32_t get() const {
        return value;
    }

  protected:
    std::uint32_t value;
};
}
