#pragma once

#include <cstddef>
#include <cstdint>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// MatchEventIndicator bit set
struct MatchEventIndicator {

    // underlying type
    using type = std::uint8_t;

    static constexpr const char* name = "Match Event Indicator";
    static constexpr std::size_t size = 1;

    struct mask {
        static const type LastTradeMsg = 0x01;
        static const type LastVolumeMsg = 0x02;
        static const type LastQuoteMsg = 0x04;
        static const type LastStatsMsg = 0x08;
        static const type LastImpliedMsg = 0x10;
        static const type RecoveryMsg = 0x20;
        static const type Reserved = 0x40;
        static const type EndOfEvent = 0x80;
    };

    // default constructor
    constexpr MatchEventIndicator()
     : value{ 0 } {}

    // LastTradeMsg
    [[nodiscard]] constexpr bool LastTradeMsg() const {
        return value & mask::LastTradeMsg;
    }

    // LastVolumeMsg
    [[nodiscard]] constexpr bool LastVolumeMsg() const {
        return value & mask::LastVolumeMsg;
    }

    // LastQuoteMsg
    [[nodiscard]] constexpr bool LastQuoteMsg() const {
        return value & mask::LastQuoteMsg;
    }

    // LastStatsMsg
    [[nodiscard]] constexpr bool LastStatsMsg() const {
        return value & mask::LastStatsMsg;
    }

    // LastImpliedMsg
    [[nodiscard]] constexpr bool LastImpliedMsg() const {
        return value & mask::LastImpliedMsg;
    }

    // RecoveryMsg
    [[nodiscard]] constexpr bool RecoveryMsg() const {
        return value & mask::RecoveryMsg;
    }

    // Reserved
    [[nodiscard]] constexpr bool Reserved() const {
        return value & mask::Reserved;
    }

    // EndOfEvent
    [[nodiscard]] constexpr bool EndOfEvent() const {
        return value & mask::EndOfEvent;
    }

  protected:
    type value;
};
}
