// B3.B3Derivatives.BinaryUmdf.Sbe.v2.2: bitfields/MatchEventIndicator.hpp
#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// MatchEventIndicator bit set
struct MatchEventIndicator {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Match Event Indicator";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type Implied = 0x10;
        static const type RecoveryMsg = 0x20;
        static const type EndOfEvent = 0x80;
    };

    // default constructor
    constexpr MatchEventIndicator()
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
