#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_9 {

// MatchEventIndicator bit set
struct MatchEventIndicator {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Match Event Indicator";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type UnusedMatchEventIndicator0 = 0x01;
        static const type UnusedMatchEventIndicator1 = 0x02;
        static const type UnusedMatchEventIndicator2 = 0x04;
        static const type UnusedMatchEventIndicator3 = 0x08;
        static const type Implied = 0x10;
        static const type RecoveryMsg = 0x20;
        static const type UnusedMatchEventIndicator6 = 0x40;
        static const type EndOfEvent = 0x80;
    };

    // default constructor
    constexpr MatchEventIndicator()
     : value{ 0 } {}

    // Unused MatchEventIndicator 0
    [[nodiscard]] constexpr bool UnusedMatchEventIndicator0() const {
        return value & mask::UnusedMatchEventIndicator0;
    }

    // Unused MatchEventIndicator 1
    [[nodiscard]] constexpr bool UnusedMatchEventIndicator1() const {
        return value & mask::UnusedMatchEventIndicator1;
    }

    // Unused MatchEventIndicator 2
    [[nodiscard]] constexpr bool UnusedMatchEventIndicator2() const {
        return value & mask::UnusedMatchEventIndicator2;
    }

    // Unused MatchEventIndicator 3
    [[nodiscard]] constexpr bool UnusedMatchEventIndicator3() const {
        return value & mask::UnusedMatchEventIndicator3;
    }

    // Implied
    [[nodiscard]] constexpr bool Implied() const {
        return value & mask::Implied;
    }

    // RecoveryMsg
    [[nodiscard]] constexpr bool RecoveryMsg() const {
        return value & mask::RecoveryMsg;
    }

    // Unused MatchEventIndicator 6
    [[nodiscard]] constexpr bool UnusedMatchEventIndicator6() const {
        return value & mask::UnusedMatchEventIndicator6;
    }

    // EndOfEvent
    [[nodiscard]] constexpr bool EndOfEvent() const {
        return value & mask::EndOfEvent;
    }

  protected:
    type value;
};
}
