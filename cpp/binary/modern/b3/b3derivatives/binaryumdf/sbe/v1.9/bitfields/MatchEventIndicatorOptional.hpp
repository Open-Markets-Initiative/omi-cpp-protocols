// B3.B3Derivatives.BinaryUmdf.Sbe.v1.9: bitfields/MatchEventIndicatorOptional.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// MatchEventIndicator bit set
struct MatchEventIndicatorOptional {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Match Event Indicator Optional";
    static constexpr std::size_t size = 1;
    static const type no_value = 255;

    struct mask {
        static const type Implied = 0x10;
        static const type RecoveryMsg = 0x20;
        static const type EndOfEvent = 0x80;
    };

    // default constructor
    constexpr MatchEventIndicatorOptional()
     : value{ 0 } {}

    // Implied
    [[nodiscard]] constexpr bool Implied() const {
        return value & mask::Implied;
    }

    // RecoveryMsg
    [[nodiscard]] constexpr bool RecoveryMsg() const {
        return value & mask::RecoveryMsg;
    }

    // EndOfEvent
    [[nodiscard]] constexpr bool EndOfEvent() const {
        return value & mask::EndOfEvent;
    }

    // all bits
    [[nodiscard]] constexpr type get() const {
        return value;
    }

  protected:
    type value;
};
}
