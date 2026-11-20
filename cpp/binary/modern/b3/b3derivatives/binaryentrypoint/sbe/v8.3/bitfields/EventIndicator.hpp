// B3.B3Derivatives.BinaryEntryPoint.Sbe.v8.3: bitfields/EventIndicator.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// EventIndicator bit set
struct EventIndicator {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Event Indicator";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type PossResend = 0x01;
        static const type LowPriority = 0x02;
    };

    // default constructor
    constexpr EventIndicator()
     : value{ 0 } {}

    // PossResend
    [[nodiscard]] constexpr bool PossResend() const {
        return value & mask::PossResend;
    }

    // LowPriority
    [[nodiscard]] constexpr bool LowPriority() const {
        return value & mask::LowPriority;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
